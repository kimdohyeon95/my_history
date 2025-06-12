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








