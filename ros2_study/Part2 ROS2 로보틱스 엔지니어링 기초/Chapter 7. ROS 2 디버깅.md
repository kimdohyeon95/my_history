## Ch07-01 ROS 2 환경에서 디버깅하는 방법들
---

 ### 다양한 목적의 디버깅 도구들 

  #### Logger 

   <div align="left">
     <img src="https://github.com/user-attachments/assets/00be7819-c315-4c2a-8345-988ba4b2e8db" height="350" width="600">
   </div>

  - Debug
     - 변수의 값이나 상태가 변화되는 것을 기록할 때 사용. 동작을 세부적으로 이해해야 할 때. 

       개발 단계에서 디버그 레벨로 세팅하여 사용.

  - Warn
    - 시스템이 정상적으로 작동하고 있지만, 예상치 못한 문제가 발생하거나 앞으로 문제가 될 수 있는

      상황에 대하여 알려줘야 할 때, 사용.

  - Info 
    - 일반적인 운영정보를 나타내고, 로봇 시스템이 예상대로 정상적으로 작동하고 있는지를

      확인하는 용도롤 사용. 
  
  - error 
    - 시스템의 정상적인 작동을 방해하는 심각한 문제가 발생했을 때 사용.

  - fatal 
    -  완전히 시스템이 계속 작동할 수 없을 정도의 심각한 에러가 발생했을 때 사용. 

  #### Rviz2

  <div align="left">
     <img src="https://github.com/user-attachments/assets/92f8cff1-a8bf-4c15-b8ea-a1eb1eb0e2f2" height="350" width="600">
   </div>

  #### RQt 

  <div align="left">
     <img src="https://github.com/user-attachments/assets/360441b5-1e8e-40c5-878a-46f9fb5c503a" height="350" width="600">
   </div>

  #### rosbag2 

  <div align="left">
     <img src="https://github.com/user-attachments/assets/4e0b2232-29e3-4b1e-b06a-199a79cf4aec" height="350" width="600">
   </div>

  ####  ROS2 Doctor 

  <div align="left">
     <img src="https://github.com/user-attachments/assets/0e2bf227-ebbb-411c-87d0-7e18ccba5e09" height="350" width="600">
   </div>

## Ch07-02. (실습) Logger
--- 

 ### Logger 활용 실습

 ```bash
 ros2 pkg create --build-type ament_python logger_test --dependencies rclpy
 ```

 - logger_test라는 이름의 새 패키지를 종속성으로 rclpy를 적용하여 생성.

 ```bash
 import rclpy
 from rclpy.node import Node
 
 class LogDemo(Node):
     def __init__(self):
         # call super() in the constructor in order to initialize the Node object
         # the parameter we pass is the node name
         super().__init__('logger_example')
         # Logger level configuration
         rclpy.logging.set_logger_level('logger_example', rclpy.logging.LoggingSeverity.DEBUG)
         # create a timer sending two parameters:
         # - the duration between 2 callbacks (0.2 seeconds)
         # - the timer function (timer_callback)
         self.create_timer(0.2, self.timer_callback)
 
     def timer_callback(self):
         # print a ROS2 log debugging
         self.get_logger().debug("print a ROS2 log debugging")
         # print a ROS2 log info
         self.get_logger().info("print a ROS2 log info")
         # print a ROS2 log warning
         self.get_logger().warn("print a ROS2 log warning")
         # print a ROS2 log error
         self.get_logger().error("print a ROS2 log error")
         # print a ROS2 log fatal
         self.get_logger().fatal("print a ROS2 log fatal")
 
 def main(args=None):
     # initialize the ROS communication
     rclpy.init(args=args)
     # declare the node constructor
     log_demo = LogDemo()
     # pause the program execution, waits for a request to kill the node (ctrl+c)
     rclpy.spin(log_demo)
     # shutdown the ROS communication
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - 패키지의 `logger_test` 디렉토리에 `log_demo.py`라는 새 파일을 생성 및 위의 코드 추가
 - 0.2초 주기의 `timer_callback` 함수를 실행하여 ros2 logger의 debug 에서부터 fatal

   단계 까지의 log를 출력함.
 - `set_logger_level()` 함수를 이용하여 `rclpy.logging.LoggingSeverity.DEBUG` 처럼

   인자 설정을 통해 `DEBUG/INFO/WARN/ERROR/FATAL` 출력되는 log의 레벨을 지정하여 출력 가능.
 - ex) rclpy.logging.LoggingSeverity.INFO 의 경우 INFO를 포함한 그 이상의 Log 레벨에

   대하여 터미널에 출력 한다는 의미. 
 
 
 ```bash
 entry_points={
     'console_scripts': [
         'log_demo = logger_test.log_demo:main',
     ],
 },
 ```

 - `logger_test/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가
 
 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select logger_test
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크스페이스 루트 디렉토리에서 패키지를 다시 빌드


 ```bash
 ros2 run logger_test log_demo
 ```

 - 터미널에서 노드 실행 후 결과 확인.

 <div align="left">
     <img src="https://github.com/user-attachments/assets/1fdda4c3-7070-42bc-850d-96d15ce44658" height="350" width="400">
   </div>

 - DEBUG 레벨 부터 FATAL 레벨 까지의 Log 가 잘 출력되는 것을 확인 할 수 있다.

 ```bash
 rclpy.logging.set_logger_level('logger_name', rclpy.logging.LoggingSeverity.<LOG_LEVEL>)
 ```

 - `log_demo.py`에서 로그 레벨을 변경하고 선택한 레벨에 따라 다른 메시지가 인쇄되는지 여부를 확인
 - `rclpy.logging.LoggingSeverity.WARN` 로 변경 후 결과를 확인

 <div align="left">
     <img src="https://github.com/user-attachments/assets/299c2a6a-520b-41cf-990f-3a8efb0e1440" height="350" width="450">
 </div>

 - WARN 레벨 이상의 Log가 잘 출력되는 것을 알 수 있다. 
 
 ```bash
 export ROS_LOG_DIR=/path/to/custom/log/directory
 ```

 - 기본 로그 저장 위치
   - Linux의 경우: ~/.ros/log 디렉토리
 - 로그 위치 변경 방법
   - 환경변수 ROS_LOG_DIR을 설정하여 다른 디렉토리로 변경 할 수 있다.
   - ROS_LOG_DIR=""로 설정하면 파일 로깅을 비활성화할 수 있다.

## Ch07-03. (실습) Rviz2
---

 ### Rviz2

 - Rviz2는 이미지, 포인트 클라우드, 레이저, 운동 변환, 로봇 모델 등을 볼 수 있는 시각화 도구이다. 
 - Rviz2는 주로 시뮬레이션 또는 실제 로봇의 퍼블리싱된 토픽을 시각화하는 목적으로 사용된다. 

 ### 시뮬레이션 환경 열기

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True world_name:=empty.world
 ```

 ### Rviz2 실습

 ```bash
 rviz2
 ```

 - rviz2 실행.
   
 <div align="left">
     <img src="https://github.com/user-attachments/assets/8a42f2f2-8411-444e-b81a-4027c6fc70c8" height="500" width="850">
   </div>

   - 중앙 패널
     - 데이터가 표시되는 곳으로 회전(마우스 왼쪽 클릭 드래그), 이동(마우스 휠 드래그 또는 Shift + 왼쪽 클릭 드래그),

       확대/축소(마우스 오른쪽 클릭 드래그)를 할 수 있는 3D 공간.

   - 디스플레이 패널
     - 중앙 패널에서 시각화하려는 모든 요소를 관리/구성.
       - `Global Option`에서 데이터 시각화 요구 사항에 가장 적합한 고정 프레임을 선택해야 한다. 고정 프레임은

           모든 데이터를 비교할 기준이 되는 프레임.
       - `Add` 버튼을 클릭하면 RVIZ2에서 시각화할 수 있는 모든 유형의 요소가 표시

   - 뷰 패널
     - 중앙 패널의 뷰를 전환할 수 있다. 

 <div align="left">
      <img src="https://github.com/user-attachments/assets/7fd2ca14-5d0a-4513-8722-881757f7d586" height="500" width="850">
 </div>

 <디스플레이 패널 > 

 - Fixed Frame
   - 어떤 프레임을 기준으로 시각화를 할 것인지 지정. 
   - gazebo 시뮬레이션 환경 안에 있는 티아고 로봇의 joint 프레임으로 부터 가져온다. 
   - fIxed_frame을 odom 으로 설정하면 odom 축을 기준으로 로봇이 움직이고 base_link(로봇의 몸통) 를 

     fixed_frame 으로 변경하면 로봇이 가만히 있는 상태에서 주변 배경이 움직이게 된다. 

 - Robot Model  
   - 로봇 모델링을 위한 Topic 이나 File(URDF) 경로를 지정해주면 로봇 모델링이 시각화 되면서 각 TF에 
     대한 이해를 도와준다.

     ( **URDF : 로봇의 모델링에 대한 내용을 기술 해놓은 파일** )

 - LaserScan 
   - 라이다 데이터를 가져오기 위해서 디스플레이 패널 하단의 Add 버튼을 누른뒤 인터페이스 타입인 LaserScan으로

     가져온 뒤 topic을  `/scan_raw`로 지정하여 가지고 오거나, 현재 시각화할 수 있는 topic들의 목록에서

     `/scan_raw`를 찾아서 적용시키는 방법이 있다.
   - 장애물이 감지되는 부분을 Point(점) 로, 중앙 패널에 표시된다.

 - PointCloud 
   - `/filtered_cloud` 토픽의 PointCloud 타입을 가져올 수 있다. PointCloud 데이터와 2D 라이다 데이터 간의 

     위치 관계가 잘 나타내어져 있는지 확인 가능하다. 

 - TF 
   - 프레임들의 시각화를 해줄 때 사용하는 디스플레이 요소.

 <뷰 프레임> 

 - Target_Frame
   - 로봇이 계속해서 이동하는 중에 로봇에 맞춰 시점을 계속해서 따라가게 해주기 위해 `Target_Frame`을 base_link로

     지정해주면 된다. 

 - Type
   - 뷰 패널의 타입을 TopDownOtho로 할 경우, Top 뷰로 위에서 내려다보는 시점으로 변경 가능하며 

     z축 회전만 가능하다. 

## Ch07-04. (실습) RQt
---

 ### RQt의 다양한 플러그인들

 <div align="left">
      <img src="https://github.com/user-attachments/assets/bffe25d3-035e-4609-b3fa-ebb9d4e39a68" height="400" width="850">
 </div>
 
 ### 시뮬레이션 환경 열기

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 ### 자주 사용되는 플러그인
 
 - Configuration
   - Dynamic Reconfigure
     - Part 4의 Navigator 부분에서 파라미터 변경 시 학습 예정. 
 - Introspection
   - Node Graph
     
    <div align="left">
      <img src="https://github.com/user-attachments/assets/a8231f22-5a08-4119-b163-a32910c073ef" height="400"                 width="850">
     </div>
 
     - Node/Topic (all)로 설정하면 현재 ROS2 시스템 상에서 등록된 모든 노드와  노드에서 나오는 토픽들을 보여준다.
     - 원으로 된 형태는 Node 직사각형 안에 들어있는 것은 토픽을 의미.
     - 어떤노드에서 토픽을 어떻게 가공되고 어느 노드에서 받아서 쓰는지를 알고 싶을 때 사용.  
 - Services
   - Service Caller

   <div align="left">
      <img src="https://github.com/user-attachments/assets/bf86ebf3-2bc9-46e4-a928-64afa6030e3d" height="400"                 width="850">
    </div>

   - 터미널 명령으로 ros2 service call 과 같이 서비스 호출하는 것을 간편하게 하기 위해 사용.
   - 서비스 이름만 알고 있으면 해당 인터페이스 타입을 알 수 있어 값만 할당해주고 Call 버튼을 누르면 

     아래 창에 Response를 받을 수 있다.
 - Topics
   - Message Publisher
   <div align="left">
      <img src="https://github.com/user-attachments/assets/6e6e2bdf-09f6-4092-aedb-5d4ba95280f9" height="400"                 width="850">
    </div>

    - ros2 시스템 상에서 활성화 되어있는 topic 들에 대해 간편하게 Publish 할 수 있는 기능이다. 
    - 발행하고자 하는 Topic을 지정해 주면 자동으로 인터페이스 타입이 정해지고 토픽 주기와 값을

      지정해주고 체크 박스를 클릭하면 발행된다. 
    - 여러개의 토픽에 대해서 동시에 발행이 가능하다.     
   - Topic Monitor
   <div align="left">
      <img src="https://github.com/user-attachments/assets/2c28ed71-cd05-4e64-bd91-84ffd62f5bf3" height="400"                 width="850">
   </div>

   - ros2 topic echo 명령어를 합쳐 놓은 것과 같아서 구독할 수 있는 모든 토픽에 대하여 나열 되어있다. 
   - 구독하길 원하는 토픽을 체크한 뒤 어떤 값으로 얼마의 주기로 발행되는지 확인할 수 있다. 
 - Visualization
   - Image View
   <div align="left">
      <img src="https://github.com/user-attachments/assets/23d8e90b-4f80-43ff-9d86-0602ccd495a8" height="400"                 width="850">
   </div>

   - 로봇에 달린 카메라로 보여지는 시야를 볼 수 있다. 
   - 로봇에 달린 카메라 관련 토픽을 선택하면 카메라 프레임 창이 띄워진다.   
   - Plot
   <div align="left">
      <img src="https://github.com/user-attachments/assets/8e45ddd6-3437-4d07-8923-5c1f0ed50da3" height="400"                 width="850">
   </div>

   - 모니터링 할 특정 토픽 데이터(속도 정보, 배터리 상태 등) 에 대해 그래프화 하여 시간에 따라

     변화 추이를 확인 할 수 있다. 
   - TF Tree
   <div align="left">
      <img src="https://github.com/user-attachments/assets/cffdd109-d148-4e4f-9afe-932bea6bd9d1" height="400"                 width="850">
   </div>

   - rviz2 디스플레이 패널에 있는 모든 프레임들에 대한 관계를 tree 형식으로 나타낸다.  

## Ch07-05. (실습) rosbag2
---

 ### rosbag2 

  #### 시뮬레이션 환경 열기
  ```bash
  ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True world_name:=empty.world
  ```

  #### Recording data 
    
  ```bash
  ros2 bag record -a
  ```

  - 현재 시스템에서 사용 가능한 모든 토픽을 기록한다.
  - 녹화하는 동안 새 토픽이 나타나면 이를 추가한다.
    - 새 토픽 자동 검색 기능은 명령줄 인수 `--no-discovery` 를 지정하여 비활성화 가능.
   
  ```bash
  ros2 bag record <topic 1> <topic 2> … <topic N>
  ```

  - 명령어에 지정된 토픽만 선택적으로 기록한다. 
  - 지정된 토픽 중 하나가 나타나면 자동으로 인식되기 때문에 지정된 토픽이 녹화 시작 시점에 
    
    반드시 존재할 필요는 없다. 이 자동 기능은 마찬가지로 `--no-discovery`를 사용하여 비활성화할 수 있다.
  - bag file 이름은 -o, --output으로 지정할 수 있으며, 추가로 지정하지 않으면 현재 타임스탬프로 명명된

    새 폴더를 생성하고 이 폴더에 데이터를 저장한다.

  #### Simulation time 

  - ROS 2에서 Simulation time은 우리가 알고 있는 시간 체계를 사용하여 시간을 알려주는 대신 `/clock` 토픽으로

    시간 값을 게시하는 것을 의미.
  - ros2 bag record에 `--use-sim-time` 인수를 전달하면 레코드 노드에 대해 이 옵션을 켠다.
    - 실제 세계의 시간이 아닌 시뮬레이션 시간 프레임에 맞추어 데이터를 기록해야 할 필요가 있을 때 이 옵션을 사용.
    - 녹화 당시의 시간이 중요하다면 이 옵션을 사용하지 않아도 된다.

  #### Splitting files during recording

  - rosbag2는 bag 파일이 최대 크기에 도달하거나 지정된 기간이 지나면 분할하는 기능을 제공한다. 기본적으로 rosbag2는

    모든 데이터를 단일 bag 파일에 기록하지만, CLI 옵션을 사용하여 이를 변경할 수 있다.
    
  ```bash
  ros2 bag record -a -b 100000
  ```

  - 위 명령어는 bag 파일이 100kb보다 커지면 분할하도록 한다.
  - 이 옵션의 기본값은 0이며, 이는 데이터가 단일 파일에 기록됨을 의미한다.
    - 옵션을 사용할 경우 배치 크기의 단위는 바이트 단위이며 86016 보다 커야한다.
   
  ```bash
  ros2 bag record -a -d 9000
  ```

  - 위 명령어는 9000초 후에 bag 파일을 분할하도록 힌다.
  - 이 옵션의 기본값은 0으로, 데이터가 단일 파일에 기록된다는 의미이다.

  #### Replaying data 

  ```bash
  ros2 bag play <bag>
  ```

  - 위 명령어로 저장된 bag 파일을 재생할 수 있다.
  - <bag>에 가능한 인수는 아래 두 가지 이다.
    - `metadata.yaml`과 하나 이상의 bag 파일이 포함된 디렉터리 이름
    -  `*.mcap` 또는 `*.db3`와 같은 단일 저장 파일
  - 주의 사항
    - 실제 로봇 시뮬레이션을 실행 시켜놓고 bag 파일을 play 하면 안된다.
    - 예를 들어, 2D 라이다 처럼 센서 데이터 같은 것들이 ros2 시스템 자체에서 출력되고 있고,

      이 상황에서 play를 하게되면 현재 2D 라이다 데이터와 record 할 당시의 데이터가 중복이 된다. 
    - 따라서 시뮬레이션을 모두 꺼놓은 상태로 play 해야한다.
    - rviz2 툴로 토픽이 기록된 내용들을 디스플레이 패널에서 시각화하여 볼 수 있다. 
  ```bash
  -l, --loop               # 반복 재생
  -r RATE, --rate RATE     # 재생 속도 조절 (예: 2.0 = 2배속)
  --start-offset SEC       # 시작 시간 오프셋 설정 (초 단위)
  -d SEC, --delay SEC      # 재생 시작 전 대기 시간
  -s START, --start-paused # 일시정지 상태로 시작
  ```

  - 주요 옵션 플래그로는 위의 내용들이 있다.

  #### Analyzing bag file

  ```bash
  ros2 bag info <bag_file>
  ```

  ```bash
  Files:             demo_strings.db3
  Bag size:          44.5 KiB
  Storage id:        sqlite3
  Duration:          8.501s
  Start:             Nov 28 2018 18:02:18.600 (1543456938.600)
  End                Nov 28 2018 18:02:27.102 (1543456947.102)
  Messages:          27
  Topic information: Topic: /chatter | Type: std_msgs/String | Count: 9 | Serialization Format: cdr
                     Topic: /my_chatter | Type: std_msgs/String | Count: 18 | Serialization Format: cdr
  ```

  - `ros bag info` 명령어로 bag file 정보를 확인할 수 있다.
  - 파일을 먼저 재생하지 않아도 내부 토픽 정보들을 확인할 수 있다는 장점이 있다. 
