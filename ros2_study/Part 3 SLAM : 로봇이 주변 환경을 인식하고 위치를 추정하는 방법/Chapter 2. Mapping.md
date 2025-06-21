## Ch02-01 Mapping 개요
---

 ### 2D LiDAR 기반의 Map

  #### Occupancy Grid Map (점유 격자형 지도)

  
  <div align="left">
   <img src="https://github.com/user-attachments/assets/46f72906-7095-4105-bb18-609556af71e6" height="350" width="600">
  </div>

 ### 2D LiDAR 기반의 SLAM Package

  #### 2D LiDAR 기반의 대표 SLAM Package (ROS 2)
  
  <div align="left">
   <img src="https://github.com/user-attachments/assets/4570e0f5-560b-42cf-b438-a827e52a0ad1" height="350" width="600">
  </div>

  - Loop Closure
    - 이전에 방문했던 장소를 다시 방문했을 때, 비교를 해서 지도를 최적화하거나 위치를 재보정하는 기능.  

  - 라이다 2개를 사용해야 하면,  두개의 센서 토픽을 하나로 묶어 주는 패키지를 사용하여  slam_toolbox 패키지 안에 input으로 넣어주는

    방식을 사용하거나 cartographer_ros 패키지를 사용한다. 

## Ch02-02. (실습) Cartographer SLAM
---

 ### 시뮬레이션 환경 구성

  #### 로봇 시뮬레이션 환경 구성 및 설치

  ```bash
  sudo apt update && sudo apt install -y \
  build-essential \
  cmake \
  git \
  libbullet-dev \
  python3-colcon-common-extensions \
  python3-flake8 \
  python3-pip \
  python3-pytest-cov \
  python3-rosdep \
  python3-setuptools \
  python3-vcstool \
  openssh-server \
  wget
  ```

  - 환경 구성을 위해 필요한 요소들을 설치한다.

  ```bash
  mkdir -p ~/nav2_ws/src
  cd ~/nav2_ws/
  wget https://raw.githubusercontent.com/Adlink-ROS/neuronbot2_ros2.repos/humble/neuronbot2_ros2.repos
  vcs import src < neuronbot2_ros2.repos
  ```

  - 새로운 워크스페이스 `nav2_ws`를 생성하고 필요한 리소스들을 가져온다.  

  ```bash
  cd ~/nav2_ws/
  rosdep update
  rosdep install --from-paths src --ignore-src -r -y --rosdistro humble
  ```

  - 워크 스페이스 안의 모든 외존성 패키지들을 설치한다. 

  ```bash
  cd ~/nav2_ws/
  colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release
  
  source ~/nav2_ws/install/local_setup.bash # 또는 새 터미널 열기
  ```

  - 워크스페이스 내 패키지들을 빌드한다. 
  - 패키지를 빌드 하고나서 install 디렉토리 안의 `local_setup.zsh` 혹은 `local_setup.bash` 파일을 

    source 명령어로 읽어오는 것을 .zshrc 혹은 .bashrc 파일에 저장해 놓으면 새 터미널 실행 시 

    자동으로 읽어 오도록 한다.

  #### 시뮬레이션 환경 열기 및 간단한 제어
    
  ```bash
  ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py
  ```

  - `ros2 launch` 명령어로 아래 두개의 환경 중 원하는 환경을 열어준다.
  - `neuronbot2_world.launch.py`의 28번째 줄의 파일을 수정하여 world를 바꿀 수 있다.
<br>

  - **Mememan world** (`mememan_world.model`)
    
  <div align="left">
   <img src="https://github.com/user-attachments/assets/ae6ecc7e-9d36-49ac-b30d-79a156f43eba" height="350" width="600">
  </div>

  - **Phenix world** (`phenix_world.model`)
    
  <div align="left">
   <img src="https://github.com/user-attachments/assets/60da43ab-23c7-417f-8f76-aa0783428db1" height="350" width="600">
  </div>

  ```bash
  ros2 run teleop_twist_keyboard teleop_twist_keyboard
  ```
  <div align="left">
   <img src="(https://github.com/user-attachments/assets/e803b8f6-6aab-42f9-990b-e6bce8c6321d" height="350" width="600">
  </div>

  - `teleop_twist_keyboard` 노드를 실행하여 위 gazebo 시뮬레이션 환경에서 로봇을 키보드로 제어할 수 있다.

 ### Cartographer 수행을 위한 준비 

  #### Launch 파일

  ```bash
  
  Node(
      package='cartographer_ros',
      executable='cartographer_node',
      name='cartographer_node',
      output='screen',
      parameters=[{'use_sim_time': use_sim_time}],
      arguments=[
          '-configuration_directory', cartographer_config_dir,
          '-configuration_basename', configuration_basename]),
  
  Node(
      package='cartographer_ros',
      executable='cartographer_occupancy_grid_node',
      name='occupancy_grid_node',
      output='screen',
      parameters=[{'use_sim_time': use_sim_time}],
      arguments=['-resolution', resolution, '-publish_period_sec', publish_period_sec]),
  ```

  - `~/nav2_ws/src/neuronbot2/neuronbot2_slam/launch/cartographer_launch.py`에서 cartographer_ros 패키지의

    두 가지 노드가 사용된다.

  ```bash
  cartographer_config_dir = LaunchConfiguration('cartographer_config_dir', 
  default=os.path.join(get_package_share_directory('neuronbot2_slam') , 'config'))
  configuration_basename = LaunchConfiguration('configuration_basename', default='cartographer.lua')
  ```
