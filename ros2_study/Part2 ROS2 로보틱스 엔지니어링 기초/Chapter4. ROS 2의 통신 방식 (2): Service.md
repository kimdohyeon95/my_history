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
    <img src="https://github.com/user-attachments/assets/95a8931f-ea67-44a5-962a-4bf6c708a237" height="150" width="200">
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
    















































![image]()
![image]()








