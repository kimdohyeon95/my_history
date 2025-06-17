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

## Ch06-02. Executor & Callback Group
---

 ### Executor 

  #### Executor 이란? 

  <div align="left">
      <img src="https://github.com/user-attachments/assets/abda4db2-36f1-4380-b30d-af882de99af4" height="350" width="650">
  </div>

  #### Executor의 종류

  <div align="left">
      <img src="https://github.com/user-attachments/assets/1f20bd18-dae3-4aef-93ee-e0f0416679ee" height="350" width="650">
  </div>

 ### Callback Group 

  #### Callback Group 그룹이란?

 <div align="left">
      <img src="https://github.com/user-attachments/assets/5a7c6a97-354e-466e-b2e0-f658e29afafc" height="350" width="650">
  </div>

  #### Callback Group의 종류 
  
  <div align="left">
      <img src="https://github.com/user-attachments/assets/399c170a-6128-4923-a97f-782489e4f863" height="350" width="650">
  </div>

## Ch06-03. (실습) 적절한 Callback Group 사용 전략
---

 ### 문제점 요약

 - 위의 `problem.py`에서 로봇이 회전기능에 들어가자마자

   `odom_callback()` 및 `scan_callback()` 실행이 중지 되었다.

 - `odom_callback()` 및 `scan_callback()`이 `timer_callback()`에 의해 차단 되었다.

 ### Mutually Exclusive Callback Group를 통한 문제 해결

  #### [실험1] SingleThreadedExecutor()와 MutuallyExclusiveCallbackGroup() 조합

  ```bash
  ros2 launch pmb2_gazebo pmb2_gazebo.launch.py is_public_sim:=True world_name:=simple_office_with_people
  ```

  - 테스트를 위한 시뮬레이션 환경 실행.

  ``` bash
  import rclpy
  from rclpy.node import Node
  from rclpy.qos import ReliabilityPolicy, QoSProfile
  from rclpy.duration import Duration
  
  from sensor_msgs.msg import LaserScan
  from nav_msgs.msg import Odometry
  from geometry_msgs.msg import Twist
  
  from transforms3d.euler import quat2euler
  
  # Import the libraries to use executors and callback groups
  from rclpy.callback_groups import ReentrantCallbackGroup, MutuallyExclusiveCallbackGroup
  from rclpy.executors import MultiThreadedExecutor, SingleThreadedExecutor
  
  class RobotControl(Node):
      def __init__(self):
          super().__init__('solution1_node')
  
          self.seconds_sleeping = 10 # 회전할 시간을 10초로 설정
  
          # Publisher
          self.vel_pub = self.create_publisher(Twist, 'cmd_vel', 10)
          self.cmd_msg = Twist()
  
          # Callback group
          self.group = MutuallyExclusiveCallbackGroup()
  
          # Subscriber
          self.odom_sub = self.create_subscription(
              Odometry, 'mobile_base_controller/odom', self.odom_callback, 10,
              callback_group=self.group)
          self.scan_sub = self.create_subscription(
              LaserScan, 'scan_raw', self.scan_callback,
              QoSProfile(depth=10, reliability=ReliabilityPolicy.BEST_EFFORT),
              callback_group=self.group)
  
          # Timer
          self.timer = self.create_timer(0.3, self.timer_callback, callback_group=self.group)
  
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
  
      # Create a single-threaded executor
      executor = SingleThreadedExecutor()
      executor.add_node(control_node)
  
      try:
          executor.spin()
      finally:
          executor.shutdown()
          executor.destroy_node()
      rclpy.shutdown()
  
  
  if __name__ == '__main__':
      main()
  ```

  - node_exercise/node_exercise/solution1.py 파일을 생성하고 위의 코드를 작성 
  - `odom_callback()`, `scan_callback()`, `timer_callback()` 함수를 모두

    mutually-exclusive 콜백 그룹으로 지정하고, singleThread로 노드 실행.

  ```bash
  entry_points={
      'console_scripts': [
          'problem_node = node_exercise.problem:main',
          'solution1_node = node_exercise.solution1:main',
      ],
  },
  ```

  - `node_exercise/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

  ```bash
  cd ~/ros2_ws
  colcon build --symlink-install --packages-select node_exercise
  source ~/ros2_ws/install/local_setup.bash # 환경에 따라 local_setup.zsh
  ```

  - 워크 스페이스 루트 디렉토리에서 패키지 다시 빌드
    

  ```bash
  ros2 run node_exercise solution1_node 
  ```

  - 새 터미널에서 노드 실행.

  <div align="left">
      <img src="https://github.com/user-attachments/assets/df4a34b7-a3b6-4a51-980a-a419065223e5" height="250" width="400">
  </div>

  - 위 실행 결과 이미지 처럼 기존 코드와 동일하게 로봇 회전동작에서 `odom_callback()` 함수와

    `scan_callback()` 함수가 동작하지 않는 것을 알 수 있다.
    
  - 여전히 모든 콜백이 같은 그룹에 있는 `SingleThreadExecutor()`를 사용하고 있다.
  - 따라서 노드 실행 결과가 달라지지 않는다.

  #### [실험2] MultiThreadedExecutor()와 MutuallyExclusiveCallbackGroup() 조합

  ```bash
  import rclpy
  from rclpy.node import Node
  from rclpy.qos import ReliabilityPolicy, QoSProfile, HistoryPolicy
  from rclpy.duration import Duration
  
  from sensor_msgs.msg import LaserScan
  from nav_msgs.msg import Odometry
  from geometry_msgs.msg import Twist
  
  from transforms3d.euler import quat2euler
  
  # Import the libraries to use executors and callback groups
  from rclpy.callback_groups import ReentrantCallbackGroup, MutuallyExclusiveCallbackGroup
  from rclpy.executors import MultiThreadedExecutor, SingleThreadedExecutor
  
  class RobotControl(Node):
      def __init__(self):
          super().__init__('solution2_node')
  
          self.seconds_sleeping = 10 # 회전할 시간을 10초로 설정
  
          # Publisher
          self.vel_pub = self.create_publisher(Twist, 'cmd_vel', 10)
          self.cmd_msg = Twist()
  
          # Callback group
          self.group1 = MutuallyExclusiveCallbackGroup()
          self.group2 = MutuallyExclusiveCallbackGroup()
          self.group3 = MutuallyExclusiveCallbackGroup()
  
          # Subscriber
          self.odom_sub = self.create_subscription(
              Odometry, 'mobile_base_controller/odom', self.odom_callback, 10,
              callback_group=self.group1)
          self.scan_sub = self.create_subscription(
              LaserScan, 'scan_raw', self.scan_callback,
              QoSProfile(depth=10, reliability=ReliabilityPolicy.RELIABLE, history=HistoryPolicy.KEEP_LAST,),
              callback_group=self.group2)
  
          # Timer
          self.timer = self.create_timer(0.3, self.timer_callback, callback_group=self.group3)
  
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
  
      # Create a multi-threaded executor
      executor = MultiThreadedExecutor(num_threads=3)
      executor.add_node(control_node)
  
      try:
          executor.spin()
      finally:
          executor.shutdown()
          executor.destroy_node()
      rclpy.shutdown()
  
  
  if __name__ == '__main__':
      main()
  ```

  - `odom_callback()`, `scan_callback()`, `timer_callback()` 콜백함수에

    각각 서로 다른 `MutuallyExclusiveCallbackGroup`을 지정 해준다.

  - `main()` 함수에서 `MultiThreadedExecutor` 클래스를 이용하여 쓰레드 3개를

    생성하여 각각의 콜백 그룹에 대해 할당된다. 

  ```bash
  entry_points={
      'console_scripts': [
          'problem_node = node_exercise.problem:main',
          'solution1_node = node_exercise.solution1:main',
          'solution2_node = node_exercise.solution2:main',
      ],
  },
  ```

  - `node_exercise/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

  ```bash
  cd ~/ros2_ws
  colcon build --symlink-install --packages-select node_exercise
  source ~/ros2_ws/install/local_setup.bash # 환경에 따라 local_setup.zsh
  ```

  - 워크 스페이스 루트 디렉토리에서 패키지를 다시 빌드. 


  ```bash
  ros2 run node_exercise solution2_node 
  ```

  - 터미널에서 노드를 시작하고 결과 확인. 

  <div align="left">
      <img src="https://github.com/user-attachments/assets/af1ceb65-7490-4b67-8c46-f61a65550c13" height="250" width="400">
  </div>

  - 이번 실험에서는 로봇의 회전 동작 중에도 `odom_callback()`와 `scan_callback()` 콜백함수

    호출이 실행되는 것을 확인 할 수 있다. 

  - 이는 각각의 콜백함수에 대하여 서로 다른 그룹으로 지정하여 각 그룹마다 멀티 쓰레드 3개를 할당

    했기 때문에 로봇 회전 동작 중에도 다른 쓰레드에서 odom과 scan 데이터 콜백 함수를 실행 할 수

    있다. 

 ### Reentrant Callback Group

 - ROS2의 `MutuallyExclusiveCallbackGroup`는 기본 콜백 그룹 유형
 - `MutuallyExclusiveCallbackGroup`와 `ReentrantCallbackGroup`의 주요 차이점
   - `MutuallyExclusiveCallbackGroup`
      - 이 그룹 내의 모든 콜백은 스레드 수에 관계없이, 해당 그룹에서 하나씩만 실행된다.
      - 예를 들어 하나의 콜백 그룹 내에 콜백이 3개 있고 스레드가 3개 있는 경우,

        한 번에 하나의 콜백만 실행
   - `ReentrantCallbackGroup`
      - 스레드가 충분하다면 이 그룹 내의 모든 콜백을 병렬로 실행할 수 있다.
      - 예를 들어, 동일한 `ReentrantCallbackGroup` 내에 3개의 콜백을 추가하고 2개의 스레드가

        있는 경우, 3개의 콜백 중 2개의 콜백을 동시에 실행할 수 있다.

  #### Callback Group 비교를 위한 실습

  ```bash
  import rclpy
  from rclpy.node import Node
  import time
  
  from std_srvs.srv import SetBool
  
  from rclpy.callback_groups import ReentrantCallbackGroup, MutuallyExclusiveCallbackGroup
  from rclpy.executors import MultiThreadedExecutor
  
  import argparse
  

  class DummyServer(Node):
  
      def __init__(self, args, callback_group_type="reentrant"):
  
          self.timer_flag = True
  
          super().__init__('service_start_turn')
  
          # More info here: https://docs.python.org/3/library/argparse.html
          parser = argparse.ArgumentParser(
              description='Dummy Server to Learn about Callback Groups and Threads')
  
          # Add an argument for setting the service waiting time
          parser.add_argument('-service_wait_time',
                              type=float,
                              help='Time the service will be waiting',
                              required=True)
  
          # Add an argument for setting por of the timer callback
          parser.add_argument('-timer_period',
                              type=float,
                              nargs=1,
                              metavar='TIMEOUT',
                              default=1.0,
                              help="Time period of the Callback for the timer")
  
          # Add an argument for setting the callback group type
          parser.add_argument('-callback_group_type',
                              type=str,
                              default="reentrant",
                              help="Type of Callback Groups REENTRANT of EXCLUSIVE")
  
          # Add an argument for setting the number of threads
          parser.add_argument('-threads',
                              type=int,
                              default=1,
                              help="Number of threads to use in the executor")
  
          self.args = parser.parse_args(args[1:])
   
          parser.print_help()
  
          # <rclpy.callback_groups.MutuallyExclusiveCallbackGroup object at 0x7ff58fc9e8e0>
          # By default, the Callbacks are mutually exclusive. This means that in each group, only
          # one Callback can be done: https://docs.ros2.org/foxy/api/rclpy/api/node.html
          print("## DEFAULT Node Callback Group=" + str(self.default_callback_group))
  
          self.get_logger().warning("Setting "+self.args.callback_group_type+" Groups")
          if self.args.callback_group_type == "reentrant":
              # If you set the group reentrant, any Callback inside will be executed in parallel
              # If there are enough threads
              self.group1 = ReentrantCallbackGroup()
              self.get_logger().warning("ReentrantCallbackGroup Set")
              # Both the service and the timer use the same callback group
              self.srv = self.create_service(
                  SetBool, '/dummy_server_srv', self.setbool_callback, callback_group=self.group1)
              self.timer = self.create_timer(
                  self.args.timer_period[0], self.timer_callback, callback_group=self.group1)
  
          elif self.args.callback_group_type == "exclusive":
              self.group1 = MutuallyExclusiveCallbackGroup()
              self.group2 = MutuallyExclusiveCallbackGroup()
              self.get_logger().warning("MutuallyExclusiveCallbackGroup Set")
              # Set one group for the service and another one for the timer
              self.srv = self.create_service(
                  SetBool, '/dummy_server_srv', self.setbool_callback, callback_group=self.group1)
              self.timer = self.create_timer(
                  self.args.timer_period[0], self.timer_callback, callback_group=self.group2)
  
          else:
              # You do not set groups. Therefore, they will get the default group for the Node
              self.get_logger().error("NO GROUPS SET Set")
              self.srv = self.create_service(
                  SetBool, '/dummy_server_srv', self.setbool_callback)
              self.timer = self.create_timer(
                  self.args.timer_period[0], self.timer_callback)
  
      def get_threads(self):
          return self.args.threads
  
      def setbool_callback(self, request, response):
          self.get_logger().warning("Processing Server Message...")
          self.wait_for_sec(self.args.service_wait_time)
          self.get_logger().warning("Processing Server Message...DONE")
          response.message = 'TURNING'
          # return the response parameters
          return response
  
      def wait_for_sec(self, wait_sec, delta=1.0):
          i = 0
          while i < wait_sec:
              self.get_logger().info("..."+str(i)+"[WAITING...]")
              time.sleep(delta)
              i += delta
  
      def timer_callback(self):
          self.print_dummy_msgs()
  
      def print_dummy_msgs(self):
          if self.timer_flag:
              self.get_logger().info("TICK")
              self.timer_flag = False
          else:
              self.get_logger().info("TACK")
              self.timer_flag = True
  
  
  def main(args=None):
      # To Use: ros2 service call /dummy_server_srv std_srvs/srv/SetBool data:\ false\
      # ros2 run unit5_pkg callback_groups_examples -service_wait_time 5.0 -timer_period 1.0
      # initialize the ROS communication
      rclpy.init(args=args)
      print("args==="+str(args))
      # Format the arguments given through ROS to use the arguments
      args_without_ros = rclpy.utilities.remove_ros_args(args)
      print("clean ROS args==="+str(args_without_ros))
      start_stop_service_node = DummyServer(args_without_ros)
  
      num_threads = start_stop_service_node.get_threads()
      start_stop_service_node.get_logger().info(
          'DummyServer Started with threads='+str(num_threads))
  
      executor = MultiThreadedExecutor(num_threads=num_threads)
      executor.add_node(start_stop_service_node)
  
      try:
          executor.spin()
      finally:
          executor.shutdown()
          start_stop_service_node.destroy_node()
  
      # shutdown the ROS communication
      rclpy.shutdown()
  
  
  if __name__ == '__main__':
      main()  
  ```

  - `DummyServer` 클래스
     - 지정된 시간 동안 초 단위로 print 문을 출력하며 시간을 측정하는 `/dummy_server_srv`
   
       서비스 서버 생성.
     - "TICK" , "TACK" 문자열을 번갈아가면 지정된 주기로 출력하는 타이머 생성.
     - `argparse.ArgumentParser` 클래스 객체를 이용하여, 타이머 콜백 호출주기,

        서비스 대기 시간 주기, 콜백 그룹 유형, 스레드 수 등의 요소를 시스템 변수를 통하여

        명령어로 노드 실행 시 인자를 입력하여 실행 할 수 있다. 

  ```bash
  entry_points={
      'console_scripts': [
          'problem_node = node_exercise.problem:main',
          'solution1_node = node_exercise.solution1:main',
          'solution2_node = node_exercise.solution2:main',
      ],
  },
  ```

  - `node_exercise/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

  ```bash
  cd ~/ros2_ws
  colcon build --symlink-install --packages-select node_exercise
  source ~/ros2_ws/install/local_setup.bash # 환경에 따라 local_setup.zsh
  ```

  - 워크스페이스 루트 디렉토리에서 패키지를 다시 빌드. 

  #### [실험 1] 2개의 Threads & 2개의 Mutually Exclusive Callback Group
  
  ```bash
  ros2 run node_exercise callback_groups_example -service_wait_time 5.0 -timer_period 1.0 -callback_group_type exclusive -threads 2
  ```

  - 새 터미널에서 위에서 만든 노드 실행 

  ```bash
  ros2 service call /dummy_server_srv std_srvs/srv/SetBool data:\ false
  ```

  - 서비스 호출 명령어로 두개의 콜백을 동시에 실행하여 작동 방식 확인. 

  <div align="left">
      <img src="https://github.com/user-attachments/assets/298561b3-def0-476f-b015-84c2b84872a1" height="350" width="500">
  </div>

  - 시스템 변수 인자로 2개의 멀티 쓰레드 생성 및 `Mutually Exclusive Callback Group` 타입의 콜백

    그룹을 생성하여 서로 다른 콜백 그룹에서 2개의 쓰레드를 통해서 동시에 두 콜백이 실행되는 것을 알 수 있다. 

  #### [실험 2] 2개의 Threads & 1개의 Reentrant Callback Group
  
  ```bash
  ros2 run node_exercise callback_groups_example -service_wait_time 5.0 -timer_period 1.0 -callback_group_type reentrant -threads 2
  ```

  - 새 터미널에서 위에서 만든 노드 실행 

  ```bash
  ros2 service call /dummy_server_srv std_srvs/srv/SetBool data:\ false
  ```

  - 서비스 호출 명령어로 두개의 콜백을 동시에 실행하여 작동 방식 확인. 

  <div align="left">
      <img src="https://github.com/user-attachments/assets/9acd6d33-8eb5-44ff-8642-6b3c63481efd" height="350" width="500">
  </div>

  - 시스템 변수 인자로 2개의 멀티 쓰레드 생성 및 `Reentrant Callback Group` 타입의 콜백

    그룹을 생성하여 같은 콜백 그룹에서 2개의 쓰레드를 통해서 동시에 두 콜백이 병렬 실행되는 것을 알 수 있다. 

  #### [실험 3] 1개의 Threads & 1개의 Reentrant Callback Group
  
  ```bash
  ros2 run node_exercise callback_groups_example -service_wait_time 5.0 -timer_period 1.0 -callback_group_type reentrant -threads 1
  ```

  - 새 터미널에서 위에서 만든 노드 실행

  ```bash
  ros2 service call /dummy_server_srv std_srvs/srv/SetBool data:\ false
  ```

  - 서비스 호출 명령어로 두개의 콜백을 동시에 실행하여 작동 방식 확인.

  <div align="left">
      <img src="https://github.com/user-attachments/assets/a2adc8f3-cc8c-4c9f-8eff-30efa2549c76" height="350" width="500">
  </div> 

  - 시스템 변수 인자로 1개의 멀티 쓰레드 생성 및 `Reentrant Callback Group` 타입의 콜백

    그룹을 생성하여 같은 콜백 그룹에 있으나, 2개의 콜백을 병렬로 실행 할 쓰레드가 1개로 충분하지 못하기에

    서비스 콜백 함수 `setbool_callback`가 실행되고 난 후, `timer_callback` 콜백 함수가 싫행된다. 
