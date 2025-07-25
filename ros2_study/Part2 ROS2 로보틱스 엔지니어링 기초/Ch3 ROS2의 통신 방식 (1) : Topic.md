## Ch03-01. Topic & Interface 개요 
---

 ### Interface란?

<div align="left">
  <img src="https://github.com/user-attachments/assets/91247096-f925-447c-94b9-aa02b70693ae" height="350" width="700">
</div>

 ### Topic 이란?
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/9c09f0db-43f1-4ec3-939b-dde7a32c41e2" height="350" width="700">
</div>

 - 비동기 통신
  => subscriber 가 publisher 특정 노드를 등록해야하는 과정이 없고, topic 에 해당되는 이름만 맞춰 주면

     publisher 로 부터 데이터를 받을 수 있다.

 - 다대다 통신
  => 하나의 publisher 가 여러 개의 subscriber에게 메세지를 보낼 수 있고, 하나의 topic 에 여러개의 

     publisher 가 동일한 메세지를 발행 할 수 도 있다.

 - 고유한 메시지 타입
  => publisher와 subscriber가 모두 동일한 데이터 구조를 사용할 수 있도록 정의해야 한다. 

 - 보통 topic 은 연속적으로 혹은 특정 주기로 데이터를 보낼 때 사용.
 - 
 ### Interface Type 정의: Message

<div align="left">
  <img src="https://github.com/user-attachments/assets/e7b69749-28ee-4016-ad23-8fe9ab496318" height="350" width="700">
</div>

## Ch03-02 # (실습) Topic & Interface 명령어
---

 ### Topic 필수 명령어

 ```bash
 ros2 topic -h
 ```
<div align="left">
  <img src="https://github.com/user-attachments/assets/ef419ee5-ea75-446d-b90a-04e03168584a" height="350" width="700">
</div>

 - ros2 topic 관련 명령어를 나열해준다.

  #### list

  ```bash
  ros2 topic list
  ```

 <div align="left">
  <img src="https://github.com/user-attachments/assets/fa6d1baf-6578-4f8d-b341-8d4b2b9b46a3" height="350" width="700">
</div>

 - 현재 시스템에서 활성화되는 모든 topic을 표시한다.

  ```bash
  ros2 topic list | grep cmd_vel
  ```
   <div align="left">
  <img src="https://github.com/user-attachments/assets/c3d83b71-928f-4a51-9d12-3214dd418c1f" height="150" width="400">
</div>

 - 특정 토픽을 검색하기 위해 위 처럼 활용도 가능.

  #### info 

  ```bash
  ros2 topic info <topic_name>
  ```

  <div align="left">
  <img src="https://github.com/user-attachments/assets/190ff8db-f9a8-4f05-b9e7-7609c2e53275" height="250" width="400">
</div>

  - `Type`: 해당 토픽에 대한 ROS2 인터페이스 유형
  - `Publisher count`: 토픽에 연결된 활성 Publisher의 수
  - `Subscription count`: 토픽에 연결된 활성 Subscription 수
  - 설명
    - `/cmd_vel` 토픽의 경우 로봇은 누군가 속도 명령을 게시할 때까지 기다림
    - `/scan_raw` 토픽의 처럼 Publisher가 1이고 Subscription이 0인 경우,

       로봇이 이 데이터를 게시하고 있지만 현재로서는 아무도 구독하지 않음
  
  #### echo 
  ```bash
  ros2 topic echo <topic_name>
  ```

  <div align="left">
  <img src="https://github.com/user-attachments/assets/e9964897-2849-4b3e-bb56-25d8cfe2f8d6" height="100" width="400">
</div>

 - 특정 topic에 발행되는 메시지를 실시간으로 subscribe하여 출력
 - 아무도 /cmd_vel 토픽을 Publish하지 않기 때문에 Subscribe할 데이터가 없고 아무것도 출력되지 않는다.

 ### Interface 필수 명령어 

  #### list 
  
  ```bash
  ros2 interface list
  ```

<div align="left">
  <img src="https://github.com/user-attachments/assets/fd6978bd-395b-4740-951e-5476b85bb3ef" height="350" width="500">
</div>

  - 사용 가능한 모든 인터페이스의 목록을 출력
  - 결과가 표시되는 내용을 보면 인터페이스가 다음 그룹으로 나뉘어져 있음
    - Messages: .msg 파일에서 정의되며, ROS 메시지에 대해 기술
    - Services: .srv 파일에서 정의되며, request, response 두 부분으로 구성
    - Actions: .action 파일에서 정의되며, goal, result, feedback의 세 부분으로 구성
  - 메시지에 대한 설명과 정의를 찾는 방법은 두 가지가 존재한다.
    - .msg 파일과 ROS 패키지의 msg/ 디렉터리에서 찾을 수 있음
    - .msg 파일은 필드(자료형)와 상수의 두 부분으로 구성
 
  #### show 

  ```bash
  ros2 interface show <interface_name>
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/33c0c70c-1afb-4eb9-b1d8-2a542161fc8c" height="150" width="500">
</div>

  - 특정 인터페이스에 대한 정보를 얻는 데 사용
  - 예시로 `/cmd_vel` 토픽에 대한 정보를 찾을 때 이 토픽이 `geometry_msgs/Twist`라는

    유형을 사용하고 이것이 Messages 타입의 인터페이스 라는 것을 안다.

  ```bash
  ros2 interface show geometry_msgs/msg/Twist
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/51cac134-3b62-459f-be3c-cb900ae860c5" height="350" width="500">
</div>

  - 령 출력을 보면 Twist 메시지가 두 개의 Vector3 메시지로 구성되어 있음을 알 수 있다.

    선형 속도에 대한 3차원 벡터와 각속도에 대한 또 다른 3차원 벡터로 구성된다.

  #### proto 
  
  ```bash
  ros2 interface proto <interface_name>
  ```

  - 인터페이스의 프로토타입을 보여주는 명령어

  ```bash
  ros2 interface proto geometry_msgs/msg/Twist
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/59c337e7-597d-4028-abb4-0804c084e1ae" height="350" width="500">
</div>
  
  - `/cmd_vel` 토픽에서 사용하는 메시지 타입의 프로토타입을 확인하기 위한 명령어  
  - 토픽 `/cmd_vel`에 대한 메시지를 작성하는 구조가 두 개의 3차원 벡터로 구성되어 있음을 알 수 있다.

    한 벡터는 축 x, y, z의 선형 속도이고 하고 다른 벡터는 축 x, y, z의 회전 속도 이다.

 ### Topic 필수 명령어 (2) 

  #### pub
  ```bash
  ros2 topic pub <topic_name> <interface_name> <message>
  ```

  - 특정 topic에 메시지를 발행(publish)하는 데 사용
 
  ```bash
  ros2 topic pub /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.1, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.0}}"
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/cb252ac3-9312-41c9-ab23-9d5d4b838f1d" height="350" width="500">
</div>

  - tiago_gazebo를 실행하여 ros2 topic publish 명령어로 `/cmd_vel` 토픽에
  
    선속도 linear_x 축 선속도 0.1 angular_z 축 회전속도 1.0 의 속도를 퍼블리쉬 한다.
  - 주요 옵션으로 `-r, --rate <rate>` 를 사용하여 지정된 주기(Hz)로 메시지를 발행할 수 있다.
  - 또한 `-1, --once`를 사용하여 메시지를 한 번만 발행하고 종료한다. 

  ```bash
  ros2 topic echo /cmd_vel
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/0f7de2f7-e1ea-4f2e-bb87-6597ca3c4e0c" height="350" width="500">
</div>

  - 맨 처음에 `ros2 topic echo /cmd_vel` 명령어를 실행 했을 때에는 아무것도 출력 되지 않았지만,

    지금은 위의 publish된 메시지가 있기때문에 subscription이 되고 있는 것을 확인할 수 있다. 

  ```bash
  ros2 topic info /cmd_vel
  ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/741cd9da-b60d-4867-85a5-6e696610f6b6" height="200" width="500">
</div>

  - 또한 /cmd_vel 토픽의 Publisher / Subscription 수가 증가했는지 확인할 수도 있다.
  - ros2 topic pub 명령으로 토픽에 게시하고 있으므로 Publisher 수는 1이다.
  - ros2 topic echo 명령으로 토픽을 구독하고 있으므로 Subscription 횟수가 2로 증가했다.

  #### hz 

  ```bash
  ros2 topic hz <topic_name>
  ```

  <div align="left">
  <img src="https://github.com/user-attachments/assets/2c4d68e8-c9ae-4961-9a23-3a125aa31729" height="200" width="500">
</div>

  - topic의 발행 빈도를 hz단위로 측정

  #### bw 

  ```bash
  ros2 topic bw <topic_name>
  ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/bd8736ad-26c9-47ef-b0f7-fe893fd2cc63" height="350" width="500">
</div>

  - topic의 대역폭 사용량을 측정 ( 초당 몇 바이트의 데이터를 전송하고 있는지를 나타냄)
  - 공유기와 같은 네트워크 환경 아래에서 데이터 트래픽을 측정하여 초당 얼마만큼의 데이터를 보내는 지 알 수 있다.

## Ch03-03. (실습) Topic Programming (1) - Publisher
---

 ### Topic Publisher Node
 
 ```bash
 cd ~/ros2_ws/src

 ros2 pkg create --build-type ament_python tutorial_topic --dependencies rclpy geometry_msgs
 
 cd tutorial_topic
 ```

 - ros2 퍼블리셔 연습을 위한 패키지를 생성.

 ```bash
 import rclpy
 from rclpy.node import Node
 from geometry_msgs.msg import Twist
 import time
 
 class MovePublisher(Node):
     def __init__(self):
         super().__init__('move_publisher')
         
         # Twist 메시지를 발행하는 publisher 생성
         # 토픽 이름은 '/cmd_vel', 큐 크기는 10으로 설정
         self.publisher_ = self.create_publisher(Twist, '/cmd_vel', 10)
         
         # 0.1초(10Hz) 간격으로 타이머 콜백 함수 실행
         timer_period = 0.1  # seconds
         self.timer = self.create_timer(timer_period, self.timer_callback)
         
         # 로봇의 이동 방향을 추적하기 위한 변수
         self.forward = True
         
         # 방향 전환 시간 설정 (5초)
         self.switch_time = 5.0  # seconds
         
         # 마지막 방향 전환 시간 기록
         self.last_switch_time = time.time()
         
         self.get_logger().info('MovePublisher has been started')
 
     def timer_callback(self):
         current_time = time.time()
         msg = Twist()
         
         # 5초마다 방향 전환
         if current_time - self.last_switch_time >= self.switch_time:
             self.forward = not self.forward
             self.last_switch_time = current_time
         
         if self.forward:
             msg.linear.x = 0.2  # 전진 속도 (m/s)
         else:
             msg.linear.x = -0.2  # 후진 속도 (m/s)
         
         # 계산된 속도 메시지 발행
         self.publisher_.publish(msg)
         
         # 로그 메시지 출력
         direction = "forward" if self.forward else "backward"
         self.get_logger().info(f'Moving {direction}: Linear velocity = {msg.linear.x} m/s')
 
 def main(args=None):
     rclpy.init(args=args)
     move_publisher = MovePublisher()
     rclpy.spin(move_publisher)
     move_publisher.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `tutorial_topic/tutorial_topic/move_publisher.py` 파일을 생성하고 위의 코드를 작성.
 - `create_publisher` 함수의 인자 중 첫번째는 interface의 타입으로 `/cmd_vel` 토픽의 타입은

   `Twist`를 의미한다.

    두번째 인자는 사용할 topic 의 이름이 들어가고 세번째 인자는 Queue의 Size를 지정하는 것인데,

    네트워크 환경에 따라 데이터 전송량이 많을 경우 Queue 스택에 몇개의 topic을 저장할 것인지 지정하고

    환경이 원활할 경우, 저장된 topic을 전송하는데 사용된다. 

 ```bash
 from setuptools import setup

 package_name = 'tutorial_topic'
 
 setup(
     name=package_name,
     version='0.0.1',
     packages=[package_name],
     data_files=[
         ('share/ament_index/resource_index/packages',
             ['resource/' + package_name]),
         ('share/' + package_name, ['package.xml']),
     ],
     install_requires=['setuptools'],
     zip_safe=True,
     maintainer='Your Name',
     maintainer_email='you@email.com',
     description='ROS2 tutorial package for topics',
     license='TODO: License declaration',
     tests_require=['pytest'],
     entry_points={
         'console_scripts': [
             'move_publisher = tutorial_topic.move_publisher:main',
         ],
     },
 )
 ```

 - setup.py 파일을 열고 publisher Node를 추가.

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select tutorial_topic
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ros2 run tutorial_topic move_publisher
 ```

- `--symlink-install` 옵션으로 빌드 후 `move_publisher` Node 실행.

 ```bash
 ros2 topic echo /cmd_vel
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/f2f2afcd-6d55-43ac-be86-3be171053440" height="350" width="500">
</div>
 
 <div align="left">
  <img src="https://github.com/user-attachments/assets/92644137-e05d-49b7-b815-4998fac198ad" height="200" width="500">
</div>

 - tiago_gazebo 시뮬레이션을 실행하면 시뮬레이션에서 로봇이 5초 동안 전진했다가 5초 동안 후진하는 것을

   반복하는 것을 확인할 수 있다.
 - 새 터미널을 열고 `ros2 topic echo` 명령어로 발행되는 메시지를 확인할 수 있다.
 
## Ch03-04 (실습) Topic Programming (2) - Subscriber
---

 ### Topic Subscriber Node

 ```bash
 <depend>sensor_msgs</depend>
 ```

 - 2D Lidar 센서 데이터가 interface 타입이 sensor_msgs 패키지 안에 들어 있으므로 의존성을 추가한다. 

 ```bash
 ros2 topic info /scan_raw
 ```
  <div align="left">
  <img src="https://github.com/user-attachments/assets/5a852d3c-dfa6-4243-a728-26a0f79fdd71" height="100" width="500">
</div>
 
 - tiago_gazebo 시뮬레이션 실행 후, 2D Lidar 데이터의 topic 이름인 `/scan_raw`의 interface 타입

   을 확인한다.

 ```bash
 ros2 topic hz /scan_raw
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/9bf65865-b7c1-4233-b5ec-7546aeed324b" height="200" width="500">
</div>

 - `ros2 topic hz /scan_raw`명령어로 /scan_raw 토픽의 데이터 발행 주기를 확인한다.

 ```bash
 ros2 topic echo /scan_raw     
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/689d6985-7aac-41e2-be87-c391c051caab" height="200" width="500">
</div>

 - `ros2 topic echo /scan_raw` 명령어로 /scan_raw 토픽의 데이터 구조를 확인한다.
 - `/scan_raw` 데이터
    - `angle_min`: 라이다 센서의 스캔 범위 각도의 최소값
    - `angle_max`: 라이다 센서의 스캔 범위 각도의 최대값
    - `angle_increment`: 라이다 센서 데이터의 간격
    - 'range_min`: 라이다 센서 데이터의 최소 거리
    - `range_max`: 라이다 센서 데이터의 최대 거리

  ```bash
  import rclpy
  from rclpy.node import Node
  from sensor_msgs.msg import LaserScan
  import math
  
  class LidarSubscriber(Node):
      def __init__(self):
          super().__init__('lidar_subscriber')
          self.subscription = self.create_subscription(
              LaserScan,
              '/scan_raw',
              self.listener_callback,
              10)
          self.subscription  # prevent unused variable warning
          
          self.get_logger().info('LidarSubscriber has been started')
  
      def listener_callback(self, msg):
          # 전방 180도(-90도에서 90도까지) 범위의 데이터만 처리
          front_ranges = msg.ranges[len(msg.ranges)//4:3*len(msg.ranges)//4]
          
          # 무한대 값과 0값을 제외한 유효한 거리 값 찾기
          valid_ranges = [r for r in front_ranges if r != float('inf') and r != 0.0]
          
          if valid_ranges:
              min_distance = min(valid_ranges)
              min_angle = front_ranges.index(min_distance) - len(front_ranges)//2
              min_angle_degrees = min_angle * (msg.angle_increment * 180.0 / math.pi)
              
              self.get_logger().info(f'Closest obstacle: Distance = {min_distance:.2f} m, Angle = {min_angle_degrees:.2f} degrees')
          else:
              self.get_logger().info('No obstacles detected in the front 180 degrees')
  
  def main(args=None):
      rclpy.init(args=args)
      lidar_subscriber = LidarSubscriber()
      rclpy.spin(lidar_subscriber)
      lidar_subscriber.destroy_node()
      rclpy.shutdown()
  
  if __name__ == '__main__':
      main()
```

 - `tutorial_topic/tutorial_topic/lidar_subscriber.py` 파일을 생성하고 위 코드를 작성
 - `create_subscription` 함수의 첫 번째 인자는 `/scan_raw` 토픽의 interface type,

    두번째 인자는 구독 할 topic 이름, 세번째 인자는 토픽 발행 시 마다 실행될 콜백함수

    `listener_callback`, 네번째 인자는 Queue Size 를 나타낸다.

  - `listener_callback` 함수
     - `/scan_raw`토픽의 range 리스트에서 전방 180도 범위의 데이터만 처리한다.
     - 무한대 값 `inf` 와 `0`값을 제외한 유효한 거리 값 중 최소값을 찾는다.
     - 가장 가까운 장애물의 거리와 각도를 계산하여 로그로 출력한다. 

 ```bash
 entry_points={
    'console_scripts': [
        'move_publisher = tutorial_topic.move_publisher:main',
        'lidar_subscriber = tutorial_topic.lidar_subscriber:main',
      ],
  },
 ```

 - `tutorial_topic/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select tutorial_topic
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```
 - 워크 스페이스 루트 디렉토리에서 패키지 빌드 

 ```bash
 ros2 run tutorial_topic lidar_subscriber
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/d3d4f346-417b-488e-9ed9-f02ebe0c430b" height="350" width="500">
</div>

 <div align="left">
  <img src="https://github.com/user-attachments/assets/61fa759b-c756-4ede-8282-260cb3d4b72b" height="350" width="500">
</div>
 
 - tiago_gazebo 시뮬레이션이 실행 중인 상태에서, 새 터미널을 열어 Subscriber를 실행하면

   터미널에서 tiago_gazebo 로봇 전방의 가장 가까운 장애물까지의 거리와 각도 정보가 주기적으로

   출력되는 것을 확인할 수 있다.

## Ch03-05. (실습) Topic Programming (3) - Publisher & Subscriber
---

 ### Topic Publisher & Subscriber Node

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 - tiago_gazebo 시뮬레이션 환경을 열어준다. 

 ```bash
 import rclpy
 from rclpy.node import Node
 from sensor_msgs.msg import LaserScan
 from geometry_msgs.msg import Twist
 import math
 
 class ContinuousWallFinder(Node):
     def __init__(self):
         super().__init__('continuous_wall_finder')
 
         # Subscriber 생성
         self.subscription = self.create_subscription(
             LaserScan,
             '/scan_raw',
             self.lidar_callback,
             10)
 
         # Publisher 생성
         self.publisher = self.create_publisher(Twist, '/cmd_vel', 10)
 
         # 타이머 생성 (10Hz로 동작)
         self.timer = self.create_timer(0.1, self.timer_callback)
 
         # 로봇의 상태
         self.state = 'FIND_WALL'
 
         # 전방 거리
         self.front_distance = float('inf')
 
         self.get_logger().info('Continuous Wall Finder node has been started')
 
     def lidar_callback(self, msg):
         # 전방 30도(-15도에서 15도까지) 범위의 데이터 처리
         front_ranges = msg.ranges[len(msg.ranges)//2-15:len(msg.ranges)//2+15]
 
         # 무한대 값과 0값을 제외한 유효한 거리 값 찾기
         valid_ranges = [r for r in front_ranges if r != float('inf') and r != 0.0]
 
         if valid_ranges:
             self.front_distance = min(valid_ranges)
         else:
             self.front_distance = float('inf')
 
     def timer_callback(self):
         msg = Twist()
 
         if self.state == 'FIND_WALL':
             if self.front_distance > 4.0:
                 # 좌회전
                 msg.linear.x = 0.7
                 msg.angular.z = 0.5
             else:
                 self.state = 'MOVE_TO_WALL'
                 self.get_logger().info('Wall found. Moving towards it.')
 
         elif self.state == 'MOVE_TO_WALL':
             if self.front_distance > 0.5:
                 msg.linear.x = 0.4  # 천천히 전진
             else:
                 self.state = 'FIND_NEXT_WALL'
                 self.get_logger().info('Reached wall. Finding next wall.')
 
         elif self.state == 'FIND_NEXT_WALL':
             msg.angular.z = 0.7  # 좌회전
             if self.front_distance > 4.0:
                 self.state = 'FIND_WALL'
                 self.get_logger().info('Found open space. Searching for next wall.')
 
         self.publisher.publish(msg)
         self.get_logger().info(f'State: {self.state}, Front distance: {self.front_distance:.2f}m')
 
 def main(args=None):
     rclpy.init(args=args)
     continuous_wall_finder = ContinuousWallFinder()
     rclpy.spin(continuous_wall_finder)
     continuous_wall_finder.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `tutorial_topic/tutorial_topic/continuous_wall_finder.py` 파일을 생성하고 위 코드를 작성
 - `ContinuousWallFinder` 클래스
   - `LaserScan` 메시지를 구독하여 라이다 데이터를 처리
   - `Twist` 메시지를 발행하여 로봇의 이동을 제어
   - 상태 기계(state machine)을 사용하여 로봇의 동작을 제어
 - `lidar_callback` 함수
   - 라이다 데이터를 처리하여 전방 장애물까지의 거리를 계산
 - `timer_callback` 함수
   - 로봇의 현재 상태에 따라 로봇의 이동 명령을 생성하고 발행
   - `'FIND_WALL', 'MOVE_TO_WALL', 'FIND_NEXT_WALL'` 세 가지 상태를 순환적으로 관리


- 시나리오
  - 초기 상태:`FIND_WALL`
    - 전방 거리가 4.0m 이상일 경우 => 좌회전
    - 전방 거리가 4.0m 이하일 경우 => 벽 발견 및 상태 변경 (`MOVE_TO_WALL`)
  - 상테:`MOVE_TO_WALL`
    - 전방 거리가 0.5m 이상일 경우 => 천천히 전진
    - 전방 거리가 0.5m 이하일 경우 => 정지 및 상태 변경 (`FIND_NEXT_WALL`)
  - 상태:`FIND_NEXT_WALL`
    - 로봇은 다음 벽을 찾기 위해 좌회전 수행
    - 전방 거리 4.0m 이상일 경우 => 상태 변경(`FIND_WALL`)

 ```bash
 entry_points={
     'console_scripts': [
         'move_publisher = tutorial_topic.move_publisher:main',
         'lidar_subscriber = tutorial_topic.lidar_subscriber:main',
         'continuous_wall_finder = tutorial_topic.continuous_wall_finder:main',
     ],
 },
 ```

 - `tutorial_topic/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가
 
 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select tutorial_topic
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크 스페이스 루트 디렉토리 이동 및 패키지 다시 빌드

 ```bash
 ros2 run tutorial_topic continuous_wall_finder
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/6c5f4f32-93ef-48ac-a262-e04649a59e7a" height="350" width="500">
</div>

 <div align="left">
  <img src="https://github.com/user-attachments/assets/cd4b91b4-32c5-4fd0-ac75-3b2bb7abb8a0" height="350" width="500">
</div>

 <div align="left">
  <img src="https://github.com/user-attachments/assets/4bd52544-2069-4992-bd20-b40fea11692b" height="350" width="500">
</div>

 - `continuous_wall_finder` node 를 실행 하면 tiago_gazebo 시뮬레이션 에서 로봇이 lidar 데이터에 따라

   상태를 변경해가며 벽을 찾아 이동하는 것을 확인 할 수 있다. 

## Ch03-06. (실습) Interface Programming - Topic
---

 ### 새로운 Interface 타입 개발의 필요성 
 - 기존 interface 타입으로 표현할 수 없는 데이터 구조가 필요할 때
   - ROS2에서 제공하는 표준 메시지 타입으로 충분하지 않은 경우, 프로젝트에 특화된 데이터를 표현해야 할 때 사용
 - 여러 데이터 타입을 하나의 메시지로 묶어야 할 때
   - 복잡한 센서 데이터나 로봇의 상태 정보 등 여러 종류의 데이터를 하나의 메시지로 전송하고 싶을 때 유용함
 - 시스템 간 통신을 위한 특별한 프로토콜이 필요할 때
   - 특정 애플리케이션이나 하드웨어와의 통신을 위해 커스텀 프로토콜이 필요한 경우에 사용

 ### Custom Message 만들기

 ```bash
 cd ~/ros2_ws/src
 ros2 pkg create --build-type ament_cmake custom_interfaces --dependencies rclcpp std_msgs
 ```

 - 로봇의 상태를 요약하여 표현하기 위해 custon interface 패키지를 생성하기 위해 CMake 패키지를 만든다.

 ```bash
 cd ~/ros2_ws/src/custom_interfaces
 mkdir msg
 ```

 - 새로운 패키지의 새 인터페이스를 만들기 위해 custom_interfaces 패키지 안의 msg 디렉토리 생성.

 ```bash
 float64 x
 float64 y
 float64 theta
 int32 battery_percentage
 float32 temperature
 ```
 - msg 디렉토리 안에 `RobotStatus.msg` 파일을 생성.
 - 메시지 정의 내용으로는 x, y 위치 좌표와 theta 각, 배터리 상태 및 온도를 나타낸다.

 ```bash
 cmake_minimum_required(VERSION 3.8)
 project(custom_interfaces)
 
 if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   add_compile_options(-Wall -Wextra -Wpedantic)
 endif()
 
 # find dependencies
 find_package(ament_cmake REQUIRED)
 find_package(rclcpp REQUIRED)
 find_package(std_msgs REQUIRED)
 find_package(rosidl_default_generators REQUIRED)
 # uncomment the following section in order to fill in
 # further dependencies manually.
 # find_package(<dependency> REQUIRED)
 
 if(BUILD_TESTING)
   find_package(ament_lint_auto REQUIRED)
   # the following line skips the linter which checks for copyrights
   # comment the line when a copyright and license is added to all source files
   set(ament_cmake_copyright_FOUND TRUE)
   # the following line skips cpplint (only works in a git repo)
   # comment the line when this package is in a git repo and when
   # a copyright and license is added to all source files
   set(ament_cmake_cpplint_FOUND TRUE)
   ament_lint_auto_find_test_dependencies()
 endif()
 
 rosidl_generate_interfaces(${PROJECT_NAME}
   "msg/RobotStatus.msg"
 )
 
 ament_package()
 ```

 - `find_package()`
   - 토픽, 서비스, 액션 메시지를 컴파일하는 데 필요한 종속성 패키지에 대해 기술한다.

     `package.xml`의 `<build_depend>` 및 `<exec_depend>`에 해당되는 부분

     - 위의 두 종속성을 묶어 `<depend>` 로 한번에 쓸 수 있다. 
 - `rosidl_generate_interfaces()`
    - 이 함수에는 컴파일할 이 패키지의 모든 인터페이스를 기술해준다.
  
 ```bash
 <?xml version="1.0"?>
 <?xml-model href="http://download.ros.org/schema/package_format2.xsd" schematypens="http://www.w3.org/2001/XMLSchema"?>
 <package format="3">
   <name>custom_interfaces</name> 
   <version>0.0.0</version>
   <description>TODO: Package description</description>
   <maintainer email="ubuntu@todo.todo">ubuntu</maintainer>
   <license>TODO: License declaration</license>
 
   <buildtool_depend>ament_cmake</buildtool_depend>
 
   <depend>rclcpp</depend>
   <depend>std_msgs</depend>
 
   <build_depend>rosidl_default_generators</build_depend>
   <exec_depend>rosidl_default_runtime</exec_depend>
   <member_of_group>rosidl_interface_packages</member_of_group>
 
   <test_depend>ament_lint_auto</test_depend>
   <test_depend>ament_lint_common</test_depend>
 
   <export>
     <build_type>ament_cmake</build_type>
   </export>
 </package>
 ```

 - package.xml 파일에 `<build_depend>` 빌드 의존성과 `<exec_depend>`실행 의존성 수정.

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select custom_interfaces
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 패키지 빌드하여 새 인터페이스 생성. 

 ```bash
 ros2 interface show custom_interfaces/msg/RobotStatus
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/4fdd0f02-ee68-4946-a8ff-7708f2615801" height="150" width="450">
</div>

 - 메시지가 성공적으로 생성 되었는지 확인을 위해 `ros2 interface show` 명령어 실행

 ### Custom Message를 사용한 프로그래밍 

 ```bash
 cd ~/ros2_ws/src
 ros2 pkg create --build-type ament_python custom_interface_example --dependencies rclpy custom_interfaces
 ```

 - `custom_interface_example`라는 이름의 새 패키지를 생성
 - 위에서 만든 사용자 지정 인터페이스를 사용하기 위해 새 패키지의 종속성으로 `custom_interface` 패키지를 추가

 ```bash
 import rclpy
 from rclpy.node import Node
 from custom_interfaces.msg import RobotStatus
 import random
 
 class RobotStatusPublisher(Node):
     def __init__(self):
         super().__init__('robot_status_publisher')
         self.publisher_ = self.create_publisher(RobotStatus, 'robot_status', 10)
         self.timer = self.create_timer(1.0, self.timer_callback)
         self.get_logger().info('Robot Status Publisher has been started')
 
     def timer_callback(self):
         msg = RobotStatus()
         msg.x = random.uniform(-10.0, 10.0)
         msg.y = random.uniform(-10.0, 10.0)
         msg.theta = random.uniform(-3.14, 3.14)
         msg.battery_percentage = random.randint(0, 100)
         msg.temperature = random.uniform(0.0, 50.0)
 
         self.publisher_.publish(msg)
         self.get_logger().info(f'Publishing: x={msg.x:.2f}, y={msg.y:.2f}, theta={msg.theta:.2f}, battery={msg.battery_percentage}%')
 
 def main(args=None):
     rclpy.init(args=args)
     robot_status_publisher = RobotStatusPublisher()
     rclpy.spin(robot_status_publisher)
     robot_status_publisher.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - 패키지의 `custom_interface_example` 디렉토리에 `robot_status_publisher.py`파일 작성 
 - `RobotStatusPublisher` 클래스
   - 생성자에 앞전에 만들었던 `custom_interface` 패키지의 정의했던 메시지 토픽 발행을 위한 `create_publisher`함수에

     RobotStatus 라는 interface type에 `robot_status`라는 토픽 이름으로 publisher 생성
   - `timer_callback` 함수로 x, y 위치 좌표 및 theta, 배터리 및 온도 상태 정보를 담아 토픽을 1초 주기로 발행.

 ```bash
 entry_points={
     'console_scripts': [
         'robot_status_publisher = custom_interface_example.robot_status_publisher:main',
     ],
 },
 ```

 - `custom_interface_example/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select custom_interface_example
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크스페이스 루트 디렉토리에서 패키지 다시 빌드.

 ```bash
 ros2 run custom_interface_example robot_status_publisher
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/51e0af23-1b84-4325-b6f4-9aa6638d62d8" height="250" width="450">
</div>
 
 - `robot_status_publisher` 노드를 실행하여 `custom_interface` 패키지에서 정의한 메시지를 발행하는지 결과 확인. 

 ```bash
 ros2 topic echo /robot_status
 ```
 <div align="left">
  <img src="https://github.com/user-attachments/assets/d27091c0-9c1b-4b00-b174-4660b485e8ed" height="200" width="450">
</div>

 - `ros2 topic echo` 명령어로 만들어진 interface 타입대로 토픽을 구독하는지 확인. 










