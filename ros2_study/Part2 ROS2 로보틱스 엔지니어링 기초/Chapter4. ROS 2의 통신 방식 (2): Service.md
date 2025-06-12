## Ch04-01 Service 개요 
---

 ### Service란?

  <div align="left">
    <img src="https://github.com/user-attachments/assets/6b329f42-c3bc-49e4-865c-93fcba30a40f" height="350" width="700">
  </div>

 <div align="left">
    <img src="https://github.com/user-attachments/assets/6203d948-2026-4c3e-8784-ad70d35c75a3" height="350" width="700">
  </div>
 
 - ros2 Service 통신은 메시지를 사용한 Topic 통신과는 다르게 Client가 요청을 할 때에만 서비스를 수행하는

   일회성 호출의 성격을 지닌다. 

 ### Interface Type 정의:Service 
 
 <div align="left">
    <img src="https://github.com/user-attachments/assets/178c3ea4-ab50-4b30-b152-6e811839ae29" height="350" width="700">
  </div>

 ## Ch04-02. (실습) Service 명령어
---

 ### 실습 환경 준비 

 ```bash
 cp -r ~/Downloads/moving_services ~/ros2_ws/src
 ```
 
 - `moving_services` 패키지를 다운받고 압축을 풀어준 뒤, 위의 명령어를 통해  `~/ros2_ws/src`로 이동시켜 준다.

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select moving_services
 ```

 - `moving_services` 패키지를 빌드 후, 새 터미널 실행.

 ```bash
 # new terminal 1 (시뮬레이션 환경)
  ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True 
  
  # new terminal 2 (서비스 서버)
  ros2 run moving_services spin
  
  # new terminal 3 (서비스 서버)
  ros2 run moving_services circle
 ```

 - 터미널 창 3개에서 `tiago_gazebo` 시뮬레이션 및 `moving_services` 패키지의 서비스 서버 노드들을 켜준다. 

 ### Service 필수 명령어 
 
 ```bash
 ros2 serivce -h
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/79e1fbe0-ac96-452d-a120-0bf6940ffcc4" height="350" width="700">
  </div>

 - Service 와 관련된 명령어를 나열해준다. 

 ### list
 
 ```bash
 ros2 service list
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/9d03ce4a-3b22-405b-9766-66d56dd32e63" height="300" width="500">
  </div>

 - 현재 시스템에서 사용 가능한 모든 서비스 목록을 표시
 - 다운로드 받은 `moving_services` 패키지의 `/circle` 와 `/spin` 서비스가 존재하는지 확인.  

 ### call(1)
 
 ```bash
 ros2 service call <service_name> <service_type> <value>
 ```

 - 서비스를 호출(요청 보내기) 하는데 사용.
 - 위 명령어에서 보듯이 서비스를 호출하려면 `<service_type>`이 필요

 ### type

 ```bash
 ros2 service type <service_name>
 ```

 - 서비스가 어떤 인터페이스 타입을 사용하는지 확인하는데 사용

 ```bash
 ros2 service type /circle
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/760edf86-1918-4f5f-b3e2-399637d0bf72" height="50" width="250">
  </div>

 - `/circle` 서비스가 `std_srvs/srv/Empty` 라고 하는 인터페이스로 작동한다는 것을 알 수 있다.

 ```bash
 ros2 interface show std_srvs/srv/Empty 
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/e2d27e84-65f2-4d24-afb8-78079abb3443" height="50" width="300">
  </div>

 - `ros2 interface show` 명령어로 `std_srvs/srv/Empty` 인터페이스에 대한 형식을 볼 수 있다. 
 - 기존의 서비스 형식은 요청 (request) 응답 (response) 부분으로 나뉘어져 있다.
 - `std_srvs/srv/Empty`의 경우에는 둘 다 필요 없는 유형이다.

 ```bash
 ros2 interface show std_srvs/srv/SetBool
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/5c733dd5-ebf7-4650-9384-deb8e1b20328" height="120" width="300">
  </div>

 - `std_srvs/srv/SetBool` 인터페이스 형식에 대해서 보게 되면,
    - 요청(request)
      => bool type의 data
    - 응답(response)
      => bool type의 success
      => string type의 message

 ### call (2)

 ```bash
 ros2 service call /circle std_srvs/srv/Empty
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/293dc64e-5e95-4430-98b0-5a507b539d05" height="80" width="350">
  </div>
 
 <div align="left">
    <img src="https://github.com/user-attachments/assets/92cbb82e-82ba-4c97-b20b-8511f5855983" height="350" width="500">
  </div>

 - `ros2 service call` 명령어로 '/circle` 서비스 실행
 - <service_type> 이 `std_srvs/srv/Empty`이므로 <value>가 필요 없다.
 - tiago_gazebo 시뮬레이션으로 실행 시, 원을 그리며 이동하는 것을 볼 수 있다. 

 ```bash
 ros2 service call /spin std_srvs/srv/Empty
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/99da42eb-de5a-4a26-ab4a-41de5cee27b0" height="80" width="350">
  </div>

 <div align="left">
    <img src="https://github.com/user-attachments/assets/c189cefb-36fa-4c5e-a971-13c1426ac3f0" height="350" width="500">
  </div>

 - `ros2 service call` 명령어로 '/spin` 서비스 실행
 - <service_type> 역시 `std_srvs/srv/Empty`이므로 <value>가 필요 없다.
 - tiago_gazebo 시뮬레이션으로 실행 시, 제자리에서 회전하며 이동하는 것을 볼 수 있다. 

## Ch04-03. (실습) Service Programming (1) - Client
---

 ### Service Client Node

 - 목표 
   - 앞서 실행했던 spin 또는 circle 서비스를 호출하는 서비스 클라이언트 노드 생성
   - 비동기 호출 방식(call_async)을 사용하여 서비스를 호출
   - 서비스의 사용 가능 유무 확인

 ```bash
 # new terminal 1 (시뮬레이션 환경)
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True 
 
 # new terminal 2 (서비스 서버)
 ros2 run moving_services spin
 
 # new terminal 3 (서비스 서버)
 ros2 run moving_services circle
 ```

 - 이전 실습에서 사용한 `tiago_gazebo` 시뮬레이션 환경 및 서비스 서버 Node 실행. 

 ```bash
 cd ~/ros2_ws/src
 ros2 pkg create --build-type ament_python tutorial_service --dependencies rclpy geometry_msgs std_srvs
 ```

 - Service Client Node 생성을 위한 새로운 패키지 생성
 - `/spin` 과 '/circle` 서비스와의 상호작용을 위해 `std_srvs` 인터페이스를 의존성으로 설치. 

 ```bash
 import rclpy
 from rclpy.node import Node
 from std_srvs.srv import Empty
 
 class EmptyServiceClient(Node):
     def __init__(self):
         super().__init__('empty_service_client')
         self.client = self.create_client(Empty, 'spin')  # 또는 'circle'
 
         # 클라이언트의 타입 및 이름과 일치하는 서비스를 사용할 수 있는지 1초에 한 번 확인
         while not self.client.wait_for_service(timeout_sec=1.0):
             self.get_logger().info('service not available, waiting again...')
 
         # 서비스 요청을 위한 요청 객체 생성
         self.req = Empty.Request()
 
     def send_request(self):
         self.future = self.client.call_async(self.req)
 
 def main(args=None):
     rclpy.init(args=args)
     empty_client = EmptyServiceClient()
     empty_client.send_request()
 
     while rclpy.ok():
         rclpy.spin_once(empty_client, timeout_sec=0.1)
         if empty_client.future.done():
             try:
                 response = empty_client.future.result()
             except Exception as e:
                 empty_client.get_logger().info('service call failed %r' % (e,))
             else:
                 empty_client.get_logger().info('service call completed')
             break
 
         # 서비스 서버의 response를 기다리면서 추가적인 동작 수행 가능
         empty_client.get_logger().info('additional work...!')
 
     empty_client.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `tutorial_service/tutorial_service/empty_service_client.py` 파일을 생성
 -  `EmptyServiceClient` 클래스
     -`create_client` 함수
       - Service Client 생성을 위한 함수
       - 첫번째 인자에는 Service 인터페이스 타입
       - 두번째 인자에는 Service 이름
     - `wait_for_service` 함수
        - `create_client` 함수를 통해 만들어진 클라이언트의 타입 및 이름과 일치하는

          서비스를 지정된 주기로 사용할 수 있는지 확인.
     - `self.req = Empty.Request()`
        - Empty.Request() 로 인터페이스 형식에서 넣을 수 있는 request 값이 없더라도 

          request 메시지를 보내기 위한 req 객체 생성. 
        - send_request 메소드 함수 호출 시, call_async 함수를 통해서 앞서 생성된

          request 메시지 객체를 인자로 넣어주기 위해서이다.
     - `self.future = self.client.call_async(self.req)`
        - call_async의 반환 결과를 받기 위한 future 변수는 결과 자체의 저장이 되는 것이

          아니라 추후에 호출한 서비스에 대한 응답을 받았는지 확인하는 핸들러 역할을 한다.

 - `main` 함수
    - `empty_client.send_request()`
       -  EmptyServiceClient 클래스의 인스턴스를 `empty_client`에 생성하고

          send_request 함수를 호출하여 서비스 요청. 
    ```bash
    while rclpy.ok():
         rclpy.spin_once(empty_client, timeout_sec=0.1)
         if empty_client.future.done():
             try:
                 response = empty_client.future.result()
             except Exception as e:
                 empty_client.get_logger().info('service call failed %r' % (e,))
             else:
                 empty_client.get_logger().info('service call completed')
             break
 
         # 서비스 서버의 response를 기다리면서 추가적인 동작 수행 가능
         empty_client.get_logger().info('additional work...!')
     ```

     - while 문 루프 내부에서 `spin_once`함수로 Service Server에 대한 응답을 확인한다.
     - `if empty_client.future.done():`문장으로 요청에 대한 실행이 완료 되었는지를 확인.
     - 반환 값이 true일 경우, try/execpt 구문에 따라 `response = empty_client.future.result()`함수를

       통해 응답을 받거나 호출 실패를 ros2 시스템 상에 logger로 띄운다.
     - 반환 값이 false 여서 요청에 대한 실행이 완료되지 않은 경우는, 다른 작업을 수행가능하다.   
           
 ```bash
 entry_points={
     'console_scripts': [
         'empty_service_client = tutorial_service.empty_service_client:main',
     ],
 },
 ```

 - `tutorial_service/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가
   
 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select tutorial_service
 source ~/ros2_ws/install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크 스페이스 루트에서 패키지 빌드 

 ```bash
 ros2 run tutorial_service empty_service_client
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/4af176e0-6db6-47c1-bb59-80325bc6f199" height="350" width="500">
  </div>

 <div align="left">
    <img src="https://github.com/user-attachments/assets/95a8931f-ea67-44a5-962a-4bf6c708a237" height="120" width="270">
  </div>

  - 터미널에서 서비스 클라이언트 노드 실행 및 요청/응답이 정상적으로 동작하는지 확인. 

 ### rclpy.spin vs rclpy.spin_once

  #### rclpy.spin(node)

   ```bash
   import rclpy
   from std_msgs.msg import String
   
   def callback(msg):
       print('Received message: ', msg.data)
   
   rclpy.init()
   node = rclpy.create_node('listener')
   subscription = node.create_subscription(String, 'chatter', callback, 10)
   rclpy.spin(node)  # 이 부분에서 무한 루프가 실행되며 콜백이 계속 호출됩니다.
   ```

   - 이 함수는 지정된 노드에 대해 무한 루프를 실행하여 콜백을 계속해서 호출.
   - 프로그램이 종료될 때까지 계속 실행되며, 모든 콜백, 타이머, 서비스 등이 처리될 수 있음.
   - 노드가 계속해서 실행되어야 할 때 주로 사용

  #### rclpy.spin_once(node, timeout_sec=None)

  ```bash
  import rclpy
  from std_msgs.msg import String
  
  def callback(msg):
      print('Received message: ', msg.data)
  
  rclpy.init()
  node = rclpy.create_node('listener')
  subscription = node.create_subscription(String, 'chatter', callback, 10)
  
  while rclpy.ok():
      rclpy.spin_once(node)  # 한 번의 반복 실행
      # 필요하다면 여기에서 다른 작업을 수행할 수 있습니다.
  ```

  - 이 함수는 지정된 노드에 사용 가능한 콜백을 호출.
  - 주로 while 루프 안에서 호출되고,.이렇게 하면 프로그램이 계속 실행되면서 필요에 따라 콜백을 실행하고

    다른 작업을 수행할 수 있다.

## Ch04-04. (실습) Service Programming (2) - Server
---

 ### Service Server Node

 - 목표 
  - `std_srvs/srv/SetBool` 인터페이스 타입을 활용하여 TIAGo 로봇을 제어하는 서비스 서버 노드 생성

 ```bash
 ros2 interface show std_srvs/srv/SetBool
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/e5588499-b4e1-4573-81c2-93caecc37079" height="130" width="300">
</div>

 - `SetBool` 서비스 타입에 대한 정보를 알기 위해 `ros2 interface show` 명령어 실행.
 
 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 - `tiago_gazebo` 시뮬레이션 환경 실행.

 ```bash
 import rclpy
 from rclpy.node import Node
 from std_srvs.srv import SetBool
 from geometry_msgs.msg import Twist
 
 class TiagoMoveServer(Node):
     def __init__(self):
         super().__init__('tiago_move_server')
         self.srv = self.create_service(SetBool, 'tiago_move', self.tiago_move_callback)
         self.publisher_ = self.create_publisher(Twist, 'cmd_vel', 10)
         self.timer = self.create_timer(0.1, self.timer_callback)  # 10Hz
         self.is_moving = False # Flag to check if TIAGo is moving
         self.get_logger().info('TIAGo Move Server has been started')
 
     def tiago_move_callback(self, request, response):
         self.is_moving = request.data
 
         if self.is_moving:
             response.message = "TIAGo starts moving in a circle"
             self.get_logger().info('TIAGo starts moving in a circle')
         else:
             response.message = "TIAGo stops moving"
             self.get_logger().info('TIAGo stops moving')
 
         response.success = True # Set response success to True
         return response
 
     def timer_callback(self):
         msg = Twist()
         if self.is_moving:
             # Move in a circle
             msg.linear.x = 0.5  # 0.5 m/s
             msg.angular.z = 0.7  # 0.7 rad/s
         self.publisher_.publish(msg)
 
 def main(args=None):
     rclpy.init(args=args)
     tiago_move_server = TiagoMoveServer()
     rclpy.spin(tiago_move_server)
     tiago_move_server.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `tutorial_service/tutorial_service/tiago_move_server.py` 파일을 생성하고 다음 코드를 작성
 - `TiagoMoveServer` 클래스
    - `create_service` 함수
       - Service Server 생성을 위한 함수
       - 첫번째 인자는 Service 타입
       - 두번째 인자는 Service 이름
       - 세번째 인자는 `/tiago_move`이름의 서비스 요청이 들어왔을 때 실행될 콜백 함수
    - `tiago_move_callback`함수
       - `is_moving` 변수에 `request.data` 값을 저장한 후, is_moving 변수의 값에 따라서,

         `response.message`에 원을 그리며 회전하는 명령과 움직임을 멈추는 메시지를 저장. 
    - `timer_callback` 함수
      - `is_moving` 변수의 상태가 true 일 때, 10hz 주기로 선속도/각속도 값을 publish 하여

         회전주행 하도록 함.   
    
 ```bash
 entry_points={
     'console_scripts': [
         'empty_service_client = tutorial_service.empty_service_client:main',
         'tiago_move_server = tutorial_service.tiago_move_server:main', # 추가!
     ],
 },
 ```

 - `tutorial_service/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select tutorial_service
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크스페이스 루트 디렉토리에서 패키지 다시 빌드. 

 ```bash
 ros2 run tutorial_service tiago_move_server
 ```

 - 시뮬레이션이 실행 중인 상태에서, 새 터미널을 열고 `/tiago_move` 서비스를 위한 서비스 서버 노드를 실행

 ```bash
 # Data: true (원을 그리며 회전)
 ros2 service call /tiago_move std_srvs/srv/SetBool data:\ true
 
 # Data: false (정지)
 ros2 service call /tiago_move std_srvs/srv/SetBool data:\ false
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/1ad9d657-46f3-493f-b139-0dc8d0c04233" height="100" width="250">
</div>

<div align="left">
    <img src="https://github.com/user-attachments/assets/933131a3-5956-4458-8ee3-a15681306bf7" height="350" width="450">
</div>
 
 - `ros2 service call` 명령어로 서비스 호출
 - data 가 True 일때, tiago 로봇이 회전 주행을 하고 false 일 때, tiago 로봇이 정지하는 것을 알 수 있다. 

## Ch04-05. (실습) Interface Programming - Service
---

 ### Custom Service 만들기

 - 목표
   - 로봇의 선속도와 각속도, 그리고 이동 시간을 지정하여 로봇을 제어하기 위한 custom service인

     `MoveRobot.srv` 생성


 ```bash
 cd ~/ros2_ws/src/custom_interfaces
 mkdir srv
 cd srv
 touch MoveRobot.srv
 ```

 - 이전 실습에서 만들었던 `custom_interfaces` 패키지를 사용하여 `srv` 디렉리 생성
 - `srv` 디렉토리 아래에 `MoveRobot.srv`생성. 

 ```bash
 float64 linear_velocity  # 선속도 (m/s)
 float64 angular_velocity # 각속도 (rad/s)
 float64 duration         # 이동 시간 (초)
 ---
 bool success
 string message
 ```

 - `MoveRobot.srv` 파일에 request(요청) : 선속도/각속도/이동 시간

   response(응답) : 성공여부 / 메세지 형식의 인터페이스 정의
   

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
   "srv/MoveRobot.srv" # 추가!
 )
 
 ament_package()
 ```

 - custom_interfaces/CMakeLists.txt 파일에 새 Service `srv/MoveRobot.srv` 추가
 
 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select custom_interfaces
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 패키지를 빌드하여 앞서 정의한 `srv/MoveRobot.srv` 인터페이스 생성. 

 ```bash
 `ros2 interface list | grep custom_interfaces`
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/2e011552-96aa-4313-9904-5e63314b44e5" height="100" width="350">
</div>

 - ros2 interface list` 명령어로 정의한 인터페이스가 목록에 있는지 확인. 

 ```bash
 `ros2 interface show custom_interfaces/srv/MoveRobot`
 ```
 <div align="left">
    <img src="https://github.com/user-attachments/assets/2bea7d5d-6964-481d-969d-12a21b9f1748" height="200" width="350">
</div>

- `ros2 interface show` 명령어로 정의한 인터페이스 구조 확인.

 ### Custom Service를 사용한 프로그래밍 
 
 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 - `tiago_gazebo` 시뮬레이션 환경 실행.
   
 ```bash
 import rclpy
 from rclpy.node import Node
 from custom_interfaces.srv import MoveRobot
 from geometry_msgs.msg import Twist
 from nav_msgs.msg import Odometry
 import time
 
 class MovementServer(Node):
     def __init__(self):
         super().__init__('movement_server')
         self.srv = self.create_service(MoveRobot, 'move_robot', self.move_robot_callback)
         self.velocity_publisher = self.create_publisher(Twist, 'cmd_vel', 10)
 
         self.get_logger().info('TIAGo Movement Controller has been started')
 
     def move_robot_callback(self, request, response):
         twist = Twist()
         twist.linear.x = request.linear_velocity
         twist.angular.z = request.angular_velocity
 
         start_time = self.get_clock().now()
         while (self.get_clock().now() - start_time).nanoseconds / 1e9 < request.duration:
             self.velocity_publisher.publish(twist)
             time.sleep(0.1)
 
         # 로봇 정지
         stop_twist = Twist()
         self.velocity_publisher.publish(stop_twist)
         response.success = True
 
         if request.linear_velocity > 0.0 and request.angular_velocity == 0.0:
             response.message = 'Robot moved forward'
         elif request.linear_velocity < 0.0 and request.angular_velocity == 0.0:
             response.message = 'Robot moved backward'
         elif request.linear_velocity == 0.0 and request.angular_velocity > 0.0:
             response.message = 'Robot turned left'
         elif request.linear_velocity == 0.0 and request.angular_velocity < 0.0:
             response.message = 'Robot turned right'
         else:
             response.message = 'Robot moved in a curve'
 
         return response
 
 def main(args=None):
     rclpy.init(args=args)
     tiago_movement_server = MovementServer()
     rclpy.spin(tiago_movement_server)
     tiago_movement_server.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - 기존 `custom_interface_example` 패키지의 `custom_interface_example` 디렉토리에

   `movement_server.py` 라는 새 스크립트를 생성

 - `MovementServer` 클래스
    - `create_service` 함수로 `move_robot` Service Server 생성 및

      클라이언트 요청 시 콜백함수 `move_robot_callback` 실행
    - `create_publisher` 함수로 `/cmd_vel` 토픽을 발행할 `velocity_publisher` 생성. 
    - `move_robot_callback` 함수
       - 클라이언트 요청으로 들어온 `linear_velocity`, `angular_velocity`,

         데이터를 Twist 형식의 메시지 x축 선속도 / z축 회전속도에 대입.
       - `duration` 데이터의 시간동안 `velocity_publisher`를 통해 토픽 발행.
       - 그 후 로봇을 정지 시키고 `response` 응답 객체에 주행 완료 메시지 저장.  

 ```bash
 entry_points={
     'console_scripts': [
         'robot_status_publisher = custom_interface_example.robot_status_publisher:main',
         'movement_server = custom_interface_example.movement_server:main', # 추가!
     ],
 },
 ```

 - `custom_interface_example/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가


 ```bash
 cd ~/ros2_ws
 colcon build --symlink-install --packages-select custom_interface_example
 source install/local_setup.bash # 환경에 따라 local_setup.zsh
 ```

 - 워크스페이스 루트 디렉토리에서 패키지를 다시 빌드


 ```bash
 ros2 run custom_interface_example movement_server
 ```
 - `tiago_gazebo` 시뮬레이션 실행 상태에서 `/move_robot` 서비스의 서버 노드 실행.

 ```bash
 # 예시1) 5초간 전진
 ros2 service call /move_robot custom_interfaces/srv/MoveRobot "{linear_velocity: 0.2, angular_velocity: 0.0, duration: 5.0}"
 
 # 예시2) 5초간 후진
 ros2 service call /move_robot custom_interfaces/srv/MoveRobot "{linear_velocity: -0.2, angular_velocity: 0.0, duration: 5.0}"
 
 # 예시3) 10초간 제자리 회전
 ros2 service call /move_robot custom_interfaces/srv/MoveRobot "{linear_velocity: 0.0, angular_velocity: 0.5, duration: 10.0}"
 
 # 예시4) 20초간 원 그리기
 ros2 service call /move_robot custom_interfaces/srv/MoveRobot "{linear_velocity: 0.3, angular_velocity: 0.7, duration: 20.0}"
 ```
<div align="left">
    <img src="https://github.com/user-attachments/assets/4767c98a-c709-49cf-b2f8-6e27af9fd069" height="250" width="450">
</div>

<div align="left">
    <img src="https://github.com/user-attachments/assets/248f7ded-3b3d-4665-a930-4734668fffdc" height="250" width="450">
</div>

<div align="left">
    <img src="https://github.com/user-attachments/assets/6226203b-4530-4b22-8f6d-fde2f5cf80cc" height="250" width="450">
</div>

<div align="left">
    <img src="https://github.com/user-attachments/assets/3d948ebb-e8a9-4802-936c-58b6ef646334" height="250" width="450">
</div>

- `ros2 service call` 명령어로 로봇이 전진/후진/제자리 회전/원 그리기 동작 수행 결과 확인.   
 























![image]()
![image]()

![image]()
![image]()
![image]()
![image]()













































