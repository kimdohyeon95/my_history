## Ch02-01 Package, Node, Launch 개요 
---

 ### 1) 패키지(Package)란? 

<div align="left">
  <img src="https://github.com/user-attachments/assets/81d9b784-2405-487a-bd67-af846fcfe20a" height="350" width="700">
</div>

 ### 2) Python과 C++ Package 차이

<div align="left">
  <img src="https://github.com/user-attachments/assets/3e178417-1e11-40c4-b54b-56dd59d81aba" height="350" width="700">
</div>

 - Package.xml 파일은 해당 패키지를 누가 만들고 관리하는지와 패키지 빌드를 위해서 필요한 의존성 패키지에는 

   어떠한 것들이 있는지를 명시해 놓았다.

 - Python 패키지를 만들면 생성된 패키지 안에 동일한 패키지 이름의 디렉토리가 만들어져있다.

   그 안에는 해당 패키지와 관련된 python 소스코드가 존재한다.

 ### 3) 노드(Node) 란?

<div align="left">
  <img src="https://github.com/user-attachments/assets/e4897d53-82e9-4701-a260-cc39445f0345" height="350" width="700">
</div>

 ### 4) Launch 파일이란?
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/a3778d42-c62b-477a-9764-c8656962e3a6" height="350" width="700">
</div>

 - Launch 파일은 실행 할 때 몇번 포트에서 매개변수를 가져올지를 정할 수 있다. 
 - ROS2 에서는 대부분 Python 파일로 launch 파일을 만든다.

 ## 02-02 Package 실습 
---

 ```bah
 mkdir -p ~/ros2_ws/src
 cd ~/ros2_ws/src
 ```
 - ROS2 작업공간 생성

 ```bash 
 ros2 pkg create --build-type ament_python my_package --dependencies rclpy
 ```
 - ROS2 패키지 생성 명령어 `ros2 pkg create`
 - --build-type 명령어는 python 패키지 혹은 C++ 패키지 인지 결정하는 옵션
 - --dependencies 명령어는 ROS2를 성공적으로 빌드하고 런타임 도중 발생하는 오류를 막기 위해 필요한

   의존성 패키지를 명시하는 옵션

 ```bash
 cd my_package
 tree
 
 # tree 설치가 안 되었을 경우
 sudo apt install tree
 ```
- 생성된 패키지의 구조를 확인하는 명령어

 ```bash
 cd ~/ros2_ws
 colcon build
 ```
 - 워크스페이스의 루트 디렉토리로 이동하여 패키지를 빌드 해야한다.

 ```bash
 source ~/ros2_ws/install/local_setup.bash

 # 또는

 source ~/ros2_ws/install/local_setup.zsh
 ```
 - 패키지 빌드를 통해 install 폴더 안에 lib 및 share 폴더가 존재하는 것을 확인 후

   install 폴더 내에 있는 내용을 적용하기 위해 local_setup.zsh파일을 source 명령어로 읽어야 한다.  

 ```bash
 ros2 pkg list # 모든 ROS 시스템 패키지 목록을 제공
 ros2 pkg list | grep my_package # my_package인 패키지를 필터링
 ```
 - source 명령어를 실행한 후 패키지 목록을 검색했을 때 내가 생성한 패키지명이 존재하면 source가 성공한 것이다. 

 ```bash
 colcon build --symlink-install --packages-select <package_name>
 # 또는 cbp <package_name>
 ```
- colcon build 명령어로 전체 빌드를 하게되면 워크스페이스 내부에 패키지가 여러 개 있을 경우,

  변동 사항이 없는 패키지에 대해서도 빌드를 하기 때문에 시간이 오래 소요됨.

 - 따라서 변동 사항이 있는 특정 패키지에 대해서만 빌드 하기 위해 --package-select <패키지명>

   옵션 명령어를 붙여서 할 수 있음.

 - --symlink-install 옵션은 파이썬 언어와 같은 스크립트 언어에 대해서만 한정적으로 파이썬 소스코드,

   package.xml, setup.py 파일등에 대해서 수정을 할 때, 최초 한번을 빌드한 후에 빌드를 생략하겠다는

   의미이다. ( 파일 생성과 같은 경우는 제외 ) 

