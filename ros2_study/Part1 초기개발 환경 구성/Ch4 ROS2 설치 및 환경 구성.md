## Ch04-01. ROS2 Humble 설치하기
---

 ### ROS 2 Humble 설치 
 - Ubuntu 22.04 OS 에서 설치 가능한 ROS2 Humble 버전은 Ubuntu 20.04 ROS2 Foxy 버전과 다르게

   Nav2 FrameWork를 지원한다는 장점이 있다.

 - ROS2 쵝신 기능을 사용하기 위함도 있다.

  #### 1) Add the ROS2 apt repository  (설치 List 파일들을 로컬 PC로 옮긴다.) 
  
  ```bash
  sudo apt install software-properties-common
  
  sudo add-apt-repository universe
  
  sudo apt update && sudo apt install curl -y
  
  export ROS_APT_SOURCE_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F\" '{print $4}')
  
  curl -L -o /tmp/ros2-apt-source.deb "https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo $UBUNTU_CODENAME)_all.deb"
  
  sudo apt install /tmp/ros2-apt-source.deb
  ```

  #### 2) Install ROS2     
  
  ```bash
  sudo apt update
  
  sudo apt install ros-humble-desktop -> ROS2 필수 패키지들을 자동으로 모두 설치 
  
  sudo apt install ros-dev-tools -> ROS2 개발에 필요한 툴 설치 
  ```
  
  - sudo apt install ros-humble-desktop -> ROS2 필수 패키지들을 자동으로 모두 설치 
  
  - sudo apt install ros-dev-tools -> ROS2 개발에 필요한 툴 설치
  
  #### 3) Install other packages (빌드에 필요한 패키지등을 설치 한다.)

  ```bash
  `sudo apt update && sudo apt install -y build-essential cmake git libbullet-dev python3-colcon-common-extensions python3-flake8 python3-pip python3-pytest-cov python3-rosdep python3-setuptools python3-vcstool wget python3-argcomplete`
  
  `python3 -m pip install -U flake8-blind-except flake8-builtins flake8-class-newline flake8-comprehensions flake8-deprecated flake8-docstrings flake8-import-order flake8-quotes pytest-repeat pytest-rerunfailures pytest`
  
  `sudo apt install --no-install-recommends -y libasio-dev libtinyxml2-dev libcunit1-dev`
  ```

  #### 3) ROS2 Install Check 

<div align="left">
  <img src="https://github.com/user-attachments/assets/248dde4b-b7be-4049-b2f2-98bde6db7019" height="300" width="500">
</div>
<br>

  - 설치 완료 후, terminal 창에 cd /opt/ros/humble 를 입력 후 ls 로 파일목록을 살펴 ROS2 Humble 설치가 제대로 되었는지를 확인한다.

 ## Ch04-02 Workspace 생성하기 
 ---
   
  ### 1) for zsh, add to `~/.zshrc`
   
  ```bash
  source /opt/ros/humble/setup.zsh
  
  source ~/ros2_ws/install/local_setup.zsh
  
  source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.zsh
  
  source /usr/share/vcstool-completion/vcs.zsh
  
  source /usr/share/colcon_cd/function/colcon_cd.sh
  
  export _colcon_cd_root=~/ros2_ws
  
  
  # argcomplete for ros2 & colcon
  eval "$(register-python-argcomplete3 ros2)"
  
  eval "$(register-python-argcomplete3 colcon)"
  
  
  # export ROS_NAMESPACE=robot1
  
  export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
  # export RMW_IMPLEMENTATION=rmw_connext_cpp
  # export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
  # export RMW_IMPLEMENTATION=rmw_gurumdds_cpp
  
  
  # export RCUTILS_CONSOLE_OUTPUT_FORMAT='[{severity} {time}] [{name}]: {message} ({function_name}() at {file_name}:{line_number})'
  export RCUTILS_CONSOLE_OUTPUT_FORMAT='[{severity}]: {message}'
  
  export RCUTILS_COLORIZED_OUTPUT=1
  
  export RCUTILS_LOGGING_USE_STDOUT=0
  
  export RCUTILS_LOGGING_BUFFERED_STREAM=1
  
  
  alias cw='cd ~/ros2_ws'
  
  alias cs='cd ~/ros2_ws/src'
  
  alias ccd='colcon_cd'
  
  
  alias cb='cd ~/ros2_ws && colcon build --symlink-install'
  
  alias cbs='colcon build --symlink-install'
  
  alias cbp='colcon build --symlink-install --packages-select'
  
  alias cbu='colcon build --symlink-install --packages-up-to'
  
  
  alias ct='colcon test'
  
  alias ctp='colcon test --packages-select'
  
  alias ctr='colcon test-result'
  
  
  alias tl='ros2 topic list'
  
  alias te='ros2 topic echo'
  
  alias nl='ros2 node list'
  
  
  alias killgazebo='killall -9 gazebo & killall -9 gzserver & killall -9 gzclient'
  
  
  alias af='ament_flake8'
  
  alias ac='ament_cpplint'
  
  
  alias testpub='ros2 run demo_nodes_cpp talker'
  
  alias testsub='ros2 run demo_nodes_cpp listener'
  
  alias testpubimg='ros2 run image_tools cam2image'
  
  alias testsubimg='ros2 run image_tools showimage'
  
  
  alias di='rosdep install --from-paths src -y --ignore-src --os=ubuntu:jammy'
  
  
  # export ROS_DOMAIN_ID=7
  ```

  - 자신이 bash 혹은 zsh 인지에 따라서 .bashrc 혹은 .zshrc 파일에 아래의 ROS2 Humble workspace
 
    개발에 필요한 source 명령어를 추가

  - ROS2 빌드와 관련된 약어 명령어 정의 도 추가 되어있고 killgazebo 명령어 같이 gazebo 시뮬레이션 tool이

    정상적인 종료가 안될 시 관련 프로그램을 모두 종료 시켜주는 것도 포함되어 있음.

  - .zshrc 나 .bashrc 에 변경된 내용을 적용시키려면 terminal을 다시 켜야함.
  
  ### 2) Create workspace for ROS2

  ```bash
  cd # home 디렉토리로 이동
  mkdir -p ros2_ws/src
  cd ros2_ws
  colcon build --symlink-install
  # 빌드 완료 확인 후 ros2_ws에 install, build, log 디렉토리 생성됐는지 확인
  ```

  - workspace에서 colcon build를 하고나면 install 폴더 내의 local_setup.bash 파일이 생성되기 때문에

    terminal 창을 다시 열었을 때 .zsh 파일에 local_setup.bash 파일을 source 할 수 없어 발생하는 warning이 더이상 뜨지 않는다. 
  
  
