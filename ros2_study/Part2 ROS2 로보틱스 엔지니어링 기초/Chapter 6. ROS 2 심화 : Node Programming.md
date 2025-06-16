## Ch06-01. (실습) Node Programming 시, 꼭 마주치는 문제 분석하기
---

 ### 시뮬레이션 환경 구성

 ```bash
 sudo apt install ros-humble-pmb2-simulation
 pip install transforms3d
 ```

 - 로봇 시뮬레이션 환경 구성을 위해 `ros-humble-pmb2-simulation` 설치
 - `transforms3d` 패키지는 쿼터니언(Quaternion) 벡터 좌표계와 과

    오일러(Euler) 각 사이의 변환 함수를 제공 해준다.

 ```bash
 ros2 launch pmb2_gazebo pmb2_gazebo.launch.py is_public_sim:=True world_name:=simple_office_with_people
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/36b28ab4-d493-4667-8241-710506875557" height="350" width="550">
   </div>

 - `pmb_gazebo` 시뮬레이션 환경을 실행.

 ```bash
 ros2 run teleop_twist_keyboard teleop_twist_keyboard  
 ```

 - `teleop_twist_keyboard` 노드를 실행시켜 키보드를 통해 로봇 제어 가능.

 ### 노드의 문제점 분석 

 ```bash
 ros2 pkg create --build-type ament_python node_exercise --dependencies rclpy std_msgs sensor_msgs geometry_msgs nav_msgs
 ```

 - 2D 라이다 데이터, `/cmd_vel` 토픽, odometry 사용을 위해 각각

   `sensor_msgs`, `geometry_msgs`, `nav_msgs` 패키지를 의존성으로 추가하여

    새로운 패키지를 생성.

 ```bash
 import rclpy
 from rclpy.node import Node
 from rclpy.qos import ReliabilityPolicy, QoSProfile
 from rclpy.duration import Duration
 
 from sensor_msgs.msg import LaserScan
 from nav_msgs.msg import Odometry
 from geometry_msgs.msg import Twist
 
 from transforms3d.euler import quat2euler
 
 
 class RobotControl(Node):
     def __init__(self):
         super().__init__('problem_node')
 
         self.seconds_sleeping = 10 # 회전할 시간을 10초로 설정
 
         # Publisher
         self.vel_pub = self.create_publisher(Twist, 'cmd_vel', 10)
         self.cmd_msg = Twist()
 
         # Subscriber
         self.odom_sub = self.create_subscription(
             Odometry, 'mobile_base_controller/odom', self.odom_callback, 10)
         self.scan_sub = self.create_subscription(
             LaserScan, 'scan_raw', self.scan_callback,
             QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT))
 
         # Timer
         self.timer = self.create_timer(0.3, self.timer_callback)
 
         self.front_laser = 0.0 # 전방 레이저 거리
         self.roll, self.pitch, self.yaw = 0.0, 0.0, 0.0
 
     def odom_callback(self, msg: Odometry):
         self.get_logger().info("Odom CallBack")
         orientation_q = msg.pose.pose.orientation
         orientation_list = [orientation_q.x, orientation_q.y, orientation_q.z, orientation_q.w]
         self.roll, self.pitch, self.yaw = quat2euler(orientation_list)
 
     def scan_callback(self, msg: LaserScan):
         self.get_logger().info("Scan CallBack")
         self.front_laser = msg.ranges[359] # 전방 레이저 거리
 
     def stop_robot(self):
         self.cmd_msg.linear.x = 0.0
         self.cmd_msg.angular.z = 0.0
         self.vel_pub.publish(self.cmd_msg)
 
     def move_straight(self):
         self.cmd_msg.linear.x = 0.3
         self.cmd_msg.angular.z = 0.0
         self.vel_pub.publish(self.cmd_msg)
 
     def rotate(self):
         self.cmd_msg.angular.z = -0.4
         self.cmd_msg.linear.x = 0.0
 
         rotation_start_time = self.get_clock().now() # 회전 시작 시간 기록
         rotation_duration = Duration(seconds=self.seconds_sleeping)
 
         self.get_logger().info("Starting rotation for " + str(self.seconds_sleeping) + " seconds")
 
         while self.get_clock().now() - rotation_start_time < rotation_duration:
             self.vel_pub.publish(self.cmd_msg)
 
         self.get_logger().info("Rotation complete")
         self.stop_robot()
 
     def timer_callback(self):
         self.get_logger().info("Timer CallBack")
         if self.front_laser == 0.0: return
 
         try:
             self.get_logger().warning(">>> Front Range Value=" + str(self.front_laser))
             if self.front_laser > 0.5:
                 self.get_logger().info("MOVE STRAIGHT")
                 self.move_straight()
             else:
                 self.get_logger().info("STOP ROTATE")
                 self.stop_robot()
                 self.rotate()
         except:
             pass
 
 
 def main(args=None):
     rclpy.init(args=args)
     control_node = RobotControl()
     try:
         rclpy.spin(control_node)
     finally:
         control_node.destroy_node()
     rclpy.shutdown()
 
 
 if __name__ == '__main__':
     main()
 ```

 - `RobotControl` 클래스
    - `/cmd_vel` 토픽 publisher, odometry, 2D 라이다 데이터를
  
      받기 위한 subscription 생성.

    - 0.3 초 주기로 동작하는 로봇 움직임 제어를 위한 타이머 콜백함수 생성.
    - `odom_callback` 함수
       - 로봇의 현재 회전량을 쿼터니언에서 오일러 각도 형식으로 변환하여

         roll, pitch, yaw 값으로 최신화
    - `scan_callback` 함수
      - 전방 2D 라이다 데이터 최신화
    - `timer_callback 
      - 0.5m 가까이 있는 장애물을 감지할 때 까지 앞으로 이동하고

        장애물과 0.5m 보다 가까워지면 회전하는 제어를 위한 용도. 

 ```bash
 entry_points={
     'console_scripts': [
         'problem_node = node_exercise.problem:main',
     ],
 },
 ```

 ```bash
 entry_points={
     'console_scripts': [
         'problem_node = node_exercise.problem:main',
     ],
 },
 ```

 - `node_exercise/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가
   


 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select node_exercise
 source ~/ros2_ws/install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크스페이스 루트 디렉토리에서 패키지 다시 빌드

 ```bash
 ros2 run node_exercise problem_node 
 ```

 - 터미널에서 노드 실행 및 결과 확인. 

 <div align="left">
     <img src="https://github.com/user-attachments/assets/e697d794-2374-4931-be77-f7ceb0ccf6cd" height="350" width="550">
 </div>

 <div align="left">
     <img src="https://github.com/user-attachments/assets/3b6317ff-f368-4d2e-ad87-876bff382724" height="350" width="550">
   </div>

 #### 상황 붕석 
 
 - 로봇이 장애물 감지 후, 회전 기능에 들어가자마자  `odom_callback()` 및 `scan_callback()`

   실행이 중지됨.
 - 로봇이 회전 동작 중에는 다른 콜백 함수가 실행되지 않는다는 것을 알 수 있다. 

 #### 원인 분석 

 - 콜백 블로킹으로 인한 센서 데이터 수신 불가
   - scan_callback과 odom_callback이 실행되지 못한다.
   - 결과적으로 10초 동안 로봇의 센서 데이터가 완전히 손실된다.

 #### 이러한 문제가 미칠 수 있는 영향 

 - 센서 데이터의 최신화 문제
   - 현업 로봇 시스템에서는 센서 데이터가 너무 오래되면 안전상의 이유로 시스템이 중지되도록 한다.
   - 센서 데이터의 실시간성은 시스템 안전성의 핵심 요소
 - 메인 스레드가 블로킹되어 다른 중요한 시스템 이벤트 처리 불가
 - 긴급 정지 명령 등 중요한 제어 신호 수신 지연 가능성
