## Ch01-01 ROS2 개요
---

 ### 1) ROS ( Robot Operating System ) 
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/a3b127f2-b320-444a-a17c-3eae0de537a6" height="300" width="700">
</div>

 ### 2) ROS2 대표적 특징 
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/0fc128bd-957c-4bcb-8ba6-5ed7cd14343a" height="300" width="700">
</div>

 - 프로토타입과 제품간의 격차 해소 

   => ROS2 는 연구 분야 뿐만아니라 응용으로의 전환도 겨냥하였음. 이를 통해 더많은 로봇이 ROS2를 시장에 출시 할 수 있음. 

 - 마이크로컨트롤러 지원 

   => 리눅스 시스템 뿐만아니라 MCU 장비 임베디드에도 ROS를 올릴 수 있음 (Micro ROS )

 - 멀티 플랫폼지원 

   => 리눅스 뿐만아니라 맥OS 윈도우 기타시스템에 대한 지원 확대  

 - 보안 향상 

   => ROS2 는 DDS라고하는 보안기능을 이용해서 메세지의 암호화 인증 권한 관리를 지원함 (데이터의 기밀성/무결성 보장)

 - 네트워크 관리 

   => 멀티 캐스트 , 브로드캐스트, 유니 캐스트 를 모두 지원하여 유연한 환경을 제공 

 - 분산 시스템 지원 

   => 여러 로봇이 동시에 작용하거나 여러 장치가 상호작용을 하는 곳에서 통신하고 협업 할 수 있도록 설계 

 ### 3) ROS VS ROS2 Architecture 비교 
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/adc9388c-1e64-4196-8dbc-a39b712088bf" height="300" width="700">
</div>

  - ROS1 

    1. 사용자 친화적 인터페이스와 다양한 도구 제공 
  
    2. 대규모 시스템이나 복잡한 상호작용 지원에 한계 

       => 노드가 유기적으로 연결되더라도 Master 노드가 끊어지면 전체 시스템이 무너지는 문제가 발생.
  
  - ROS2 
  
    1. Master 노드가 사라지면서 더욱 유연하고 확장가능한 아키텍쳐로 되면서 대규모 로봇시스템 관리가 용이해짐. 
  
    2. DDS(Data Distribution Service)  미들웨어 채택을 해서 실시간 데이터 교환과 높은수준의 메세지 신뢰성 보장. 
  
    3. DDS는 QOS(Quality of Service)라는 설정을 제공해서 네트워크 조건이 변동되는 환경에서도 안정적인 통신을 제공 
  
    4. 포팅 / 통합을 Linux , WIndow, Mac, RTOS 와 같은 환경에서 용이하도록 만들어 개발자가 직접 선택할 수 있는

       OS의 범위를 넓혀줌.

## Ch01-02 시뮬레이션 환경 구성
---

 ```bash
 sudo apt install ros-humble-tiago-gazebo
 ```

 - binary 파일로 공개 되어 있어 빌드 패키지를 별도로 내려받을 필요없이 sudo apt install 명령어로 바로 설치 가능하다.
 - 위 명령어를 실행하면 관련된 의존성 및 Moveit이라는 로봇팔을 편리하게 제어할 수 있도록 도와주는 패키지도 모두 설치된다.

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

- binary가 아닌 source로 빌드를 할 경우 터미널 창을 새로 열어줘야 하지만, binary 이기 때문에

  현재 terminal창에서 위명령어로 gazebo 프로그램을 바로 실행 가능하다.

 <div align="left">
  <img src="https://github.com/user-attachments/assets/6efcafc0-e270-4fb8-984a-5466a4965d9f" height="350" width="700">
</div>

<br>

 ```bash
 ros2 run teleop_twist_keyboard teleop_twist_keyboard
 ```

 - 위의 teleop_twist_keyboard node를 실행시켜 로봇을 키보드로 이동시킬 수 있다.
 - tiago 패키지는 다른 로봇 패키지와 다르게 키보드 제어시 실제 주기에 맞게 움직이는 것을 잘 구현시켜 놓았다.
 

