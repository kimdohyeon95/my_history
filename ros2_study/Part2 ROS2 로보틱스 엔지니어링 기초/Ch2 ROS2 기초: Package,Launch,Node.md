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

## Ch02-03 Node 실습 
---

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```
 - tiago_gazebo 시뮬레이션 실행

 ```bash
 ros2 node list
 ```
<div align="left">
  <img src="https://github.com/user-attachments/assets/30a2cb73-a0a0-438e-bec5-cc266a981ca2" height="350" width="500">
</div>

 - 현재 실행되고 있는 Node 확인할 수 있는 명령어

 ### Node Programming 
 ```bash 
 import rclpy
 from rclpy.node import Node
 
 class TimerNode(Node):
     def __init__(self):
         super().__init__('timer_node')
         self.timer = self.create_timer(1.0, self.timer_callback)
         self.count = 0
 
     def timer_callback(self):
         self.count += 1
         self.get_logger().info(f'Hello ROS2! Count: {self.count}')
 
 def main(args=None):
     rclpy.init(args=args)
     timer_node = TimerNode()
     rclpy.spin(timer_node)
     timer_node.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
    main() 
 ```

 - RCL (ROS Client Library)
  - 다양한 프로그래밍 언어로 작성된 노드가 통신할 수 있도록 도와주는 라이브러리
  - ROS2는 다음과 같은 클라이언트 라이브러리를 유지 관리
    - `rclpy`: Python 클라이언트 라이브러리
    - `rclcpp`: C++ 클라이언트 라이브러리 
 - Node 생성 시, 일반적으로 rclpy 라이브러리의 node 모듈을 상속 받도록 class 작성을 해야한다.
 - 생성 Node 의 생성자에서 `super().init('node_name')` 함수를 통해 node 이름을 지정할 수 있다.
 - `create_timer` 함수는 지정된 주기로 timer_callback 함수를 호출하도록 한다.
 - main 문 안에서 `rclpy.init()` 함수로 Node를 초기화하고 인스턴스를 생성 후 `rclpy.spin()`함수를

   이용하여 Node를 실행 시킨다. 일반적으로 spin함수는 키보드 인터럽트가 들어오지 않는 이상 계속 실행된다.

 - `destroy_node()`함수를 통해 생성된 Node를 없애고 `rclpy.shutdown()`으로 종료한다.

 ```bash
 entry_points={
     'console_scripts': [
         'timer_node = my_package.timer:main',
     ],
 },
 ```
 - setup.py 파일에서 entry points 부분은  ` 'node_name'= package_name.source_file_name:main'`

   문장으로 해당 패키지안에 파이썬 파일을 찾아서 main문을 바탕으로 실행가능한 파일인 node를 만든다는 의미이다.

 - 빌드 한 후에 install 폴더 안에 package_name 폴더 안의 lib 폴더 안에 setup.py 에서

   생성한 Node가 파일로 있음.

 ```bash
 cd ~/ros2_ws
 colcon build
 ```
 - 워크스페이스의 루트 디렉토리로 이동하여 패키지를 다시 빌드

 ```bash
 source ~/ros2_ws/install/local_setup.bash

 # 또는
 
 source ~/ros2_ws/install/local_setup.zsh
```
 - install 폴더 내의 새로 빌드한 내용의 설치 파일을 적용하기 위해 위 명령어를 입력하거나 새로운 터미널을 열어준다.

 ```bash
 ros2 run my_package timer_node
 ```
 - 생성한 노드를  `ros2 run <package_name> <node_name>` 명령어로 실행.

 ```bash
 ros2 node list
```

 <div align="left">
  <img src="https://github.com/user-attachments/assets/63e587aa-ab2a-4752-a077-b9f284a37328" height="300" width="660">
</div>

 - 새로운 터미널을 열어 실행중인 timer_node가 목록에 나타나는지 확인.

 ```bash
 # ros2 node info <node_name>
 ros2 node info /timer_node
 ```
<div align="left">
  <img src="https://github.com/user-attachments/assets/bce03986-41e7-43f0-b637-22030227606b" height="350" width="500">
</div>

 - `ros2 node info` 명령어를 실행 시켜 현재 생성된 Node가 실행 중에 돌아가는 Publisher/Subscriber/Service 통신등에

   대한 정보들이 나타난다. 

## Ch02-04 Launch 실습
---

 ### Launch 파일 실습 
 
 ```bash
 import rclpy
 from rclpy.node import Node
 
 class FastTimerNode(Node):
     def __init__(self):
         super().__init__('fast_timer_node')
         timer_period = 0.1  # seconds
         self.timer = self.create_timer(timer_period, self.timer_callback)
         self.count = 0
 
     def timer_callback(self):
         self.count += 1
         self.get_logger().info(f'Fast Count: {self.count}')
 
 def main(args=None):
     rclpy.init(args=args)
     fast_timer_node = FastTimerNode()
     rclpy.spin(fast_timer_node)
     fast_timer_node.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - 앞서 작성한 timer_node 와 모두 동일한 내용에서 timer_callback 함수의 주기만 0.1초로 변경하였다.

 ```bash
 cd ~/ros2_ws/src/my_package
 mkdir launch
 ```
 - my_package 내에 launch 디렉토리 및 내부 launch 파일 생성.
 - 보통 launch 파일은 python 파일로 만드는데 파일명을 <launch_filename>.launch.py로 만든다.
  
 ```bash
 from launch import LaunchDescription
 from launch_ros.actions import Node
 
 def generate_launch_description():
     return LaunchDescription([
         Node(
             package='my_package',
             executable='timer_node',
             name='my_timer_node'
         ),
         Node(
             package='my_package',
             executable='fast_timer_node',
             name='my_fast_timer_node',
         )
     ])
 ```

 - launch.py 파일에 Node 의 package, executable, name은 각각 패키지 이름, setup.py 파일에서 지정한 노드 이름,
 
   ros2 시  스템 상에 등록되는 node의 이름이다. 

  ```bash
 from setuptools import setup
 import os
 from glob import glob
 
 package_name = 'my_package'
 
 setup(
     name=package_name,
     version='0.0.0',
     packages=[package_name],
     data_files=[
         ('share/ament_index/resource_index/packages',
             ['resource/' + package_name]),
         ('share/' + package_name, ['package.xml']),
         (os.path.join('share', package_name), glob('launch/*.launch.py'))
     ],
     install_requires=['setuptools'],
     zip_safe=True,
     maintainer='somebody very awesome',
     maintainer_email='user@user.com',
     description='TODO: Package description',
     license='TODO: License declaration',
     tests_require=['pytest'],
     entry_points={
         'console_scripts': [
             'timer_node = my_package.timer:main',
             'fast_timer_node = my_package.fast_timer:main',
         ],
     },
 )
 ```
 - setup.py 파일에 entry_points 부분에 기존의 timer_node 이외에 fast timer node를 추가한다. 

 - data_files 부분에는 추가로 install 디렉토리에 설치할 아이들을 적어준다. launch 디렉토리 내에

   launch.py 확장자를 가진 모든 파일을 설치하겠다는 의미이다. 

 - 이후 설정 관련한 config 디렉토리가 생길 때에는 동일하게 .yaml 을 모두 설치하도록 아래에 경로를 추가한다. 

 ```bash
 colcon build --symlink-install --packages-select my_package
 ```

<div align="left">
  <img src="https://github.com/user-attachments/assets/e8553ff7-d081-4de2-b722-4a5bdc0f6da0" height="150" width="300">
</div>

- 처음 한번만 빌드한 후 그 뒤의 수정사항에 대해서는 빌드를 할 필요가 없도록 --symlink-install 옵션을 

  넣어서 빌드한다. 

 ```bash
 ros2 launch my_package dual_timer.launch.py
 ```

<div align="left">
  <img src="https://github.com/user-attachments/assets/e3c84f08-b18b-423b-ba06-a1258f177932" height="150" width="250">
</div>

 - launch 명령어를 실행 시 2개의 노드가 동시에 동작하는 것을 확인 할 수 있다. 

 ### setup.py

  #### setup.py 의 목적 
  - Python 패키지의 메타데이터와 설치 정보를 정의하는 중요한 파일
  - 파이썬 패키지를 컴파일하는 데 필요한 내용을 포함

  #### 핵심 1: entry_points

  ```bash
  import os
  from glob import glob
  from setuptools import setup
  
  package_name = 'my_package'
  
  setup(
      
      #code
      ...
      #code
      
      entry_points={
          'console_scripts': [
              'timer_node = my_package.timer:main',
              'fast_timer_node = my_package.fast_timer:main',
          ],
      },
      
      #code
      ...
      
  )
  ```

  - 터미널에서 직접 실행할 수 있는 스크립트를 정의
  - 실행 가능한 파일을 생성하기 위해 `entry_points` 라는 딕셔너리로 작성
    - `console_scripts`라는 key와, value로 배열을 작성
      ```bash
      '<executable_name> = <package_name>.<script_name>:main'
      ```
      - 위의 경우 `timer_node`라는 새 실행 가능한 파일을 생성
      - 이 실행 가능한 파일은 `my_package`라는 패키지 안에 `timer.py` 라는 스크립트를 사용하여 생성

  #### 핵심 2: data_files 

  ```bash
  import os
  from glob import glob
  from setuptools import setup
  
  package_name = 'my_package'
  
  setup(
      
      #code
      ...
      #code
      
      data_files=[
              ('share/ament_index/resource_index/packages',
                  ['resource/' + package_name]),
              ('share/' + package_name, ['package.xml']),
              (os.path.join('share', package_name), glob('launch/*.launch.py'))
          ],
      
      #code
      ...
      #code
      
  )
  ```

  - `colcon`이 컴파일 과정에서 launch 파일을 찾으려면 `setup.py`파일의 data_files 매개 변수를

    사용하여 launch 파일을 알려주어야 한다.

  - 예를  들어, `my_package`라는 이름의 패키지를 사용하면 `launch/`폴더에 있는 모든 launch 파일

    을 `~/ros2_ws/install/my_package/share/my_package/`에 설치한다. 
