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
  - 어떤 특정 패키지를 빌드하기 위해서  여러가지 패키지가 들어 있을 수 있다. 그런 패키지를 사용할 때 vcs 명령어를

    사용하여 한번에 내려 받을 수 있다.( git clone을 여러번 사용해서 repository로 부터  내려받아야 할 때)

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

  - `cartographer_node`의 arguments로 설정 파일의 경로`(-configuration_directory)`와 설정 파일의 이름`(-configuration_basename)`

    포함되어야하기 때문에 아래 코드와 같이 사전에 정의를 해놓았다.

  ```bash
  include "map_builder.lua"
  include "trajectory_builder.lua"
  
  options = {
      map_builder = MAP_BUILDER,
      trajectory_builder = TRAJECTORY_BUILDER,
      map_frame = "map",
      tracking_frame = "base_link",
      published_frame = "odom",
      odom_frame = "odom",
      provide_odom_frame = false,
      publish_frame_projected_to_2d = true,
      use_odometry = true,
      use_nav_sat = false,
      use_landmarks = false,
      num_laser_scans = 1,
      num_multi_echo_laser_scans = 0,
      num_subdivisions_per_laser_scan = 1,
      num_point_clouds = 0,
  ```

  - 보통 ros2 에서는 config 파일로 yaml 파일을 많이 사용한다. catographer 의 경우에 .lua 확장자로 사용한다. 

    주로 catographer 관련 설정을 다룬다.

 ### Mapping 실습 

  #### 실습 환경 구성

  ```bash
  cd ~/nav2_ws/src
  git clone https://github.com/aws-robotics/aws-robomaker-bookstore-world.git -b ros2
  ```

  - `git clone`으로 시뮬레이션 환경을 내려받는다.

  ```bash
  cd ~/nav2_ws
  colcon build --symlink-install --packages-select aws_robomaker_bookstore_world
  ```

  - 내려받은 `aws_robomaker_bookstore_world` 패키지만 따로 빌드.

  ```bash
  ros2 launch aws_robomaker_bookstore_world view_bookstore.launch.py
  ```
  <div align="left">
   <img src="https://github.com/user-attachments/assets/1b3b9b4e-69f1-4a68-9014-4fd731a60c0a" height="350" width="600">
  </div> 

  - 새 터미널을 열고 시뮬레이션 환경이 잘 실행되는지 확인.

  #### 시뮬레이션 환경에 neuronbot2을 spawn하기

  - `~/nav2_ws/src/neuronbot2/neuronbot2_gazebo/launch/` 경로의 `neuronbot2_world.launch.py` 파일을 일부 수정

  ```bash
  world_model_path = os.path.join(get_package_share_directory('aws_robomaker_bookstore_world'), 'models')

  if 'GAZEBO_MODEL_PATH' in os.environ:
      os.environ['GAZEBO_MODEL_PATH'] += ":" + gazebo_model_path + ":" + world_model_path
  else :
      os.environ['GAZEBO_MODEL_PATH'] = gazebo_model_path
  ```  
  - `aws_robomaker_bookstore_world` 패키지의 models 디렉토리 안에 있는 모델들을 Gazebo가 읽을 수 있도록 환경변수에 추가.
  - 환경변수 설정을 `.bashrc` 혹은 `.zsh` 파일에 등록할 수 있지만  launch 파일 내에서 gazebo 모델 경로 정의 와 환경 변수 등록을

    해두면 launch 파일을 켤 때 환경 변수를 등록하였다가 launch 파일이 꺼지면 환경 변수에서 다시 빠지게 된다. 이로인해, gazebo 관리를

    더욱 깔끔하게 할 수 있다.

  ```bash
  world = os.path.join(
      get_package_share_directory('aws_robomaker_bookstore_world'),
      'worlds',
      'bookstore.world'
  )
  ```

  - 일부 함수들을 활용해 월드 파일이 있는 경로를 수정.

  ```bash
  ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py
  ```

  - neuronbot2가 bookstore.world에 잘 spawn되는지 위 명령어를 통해 확인

  <div align="left">
   <img src="https://github.com/user-attachments/assets/1524c317-27fb-4807-8110-b4764a200f64" height="350" width="600">
  </div> 

  #### Cartographer를 통한 SLAM 수행

  ```bash
  ros2 launch neuronbot2_slam cartographer_launch.py open_rviz:=true use_sim_time:=true
  ```

  - `neuronbot2_slam` 패키지의 launch 파일을 실행 할 때, rviz2 프로그램과 함께 실행되도록 하여

    Mapping을 수행할 수 있다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/d69f0793-6d24-4f96-9765-cfef92c70142" height="350" width="600">
  </div> 

  ```bash
  ros2 run teleop_twist_keyboard teleop_twist_keyboard
  ```

  - `teleop_twist_keyboard` 노드를 실행하여 키보드로 neuronbot2를 제어할 수 있도록 한다.

## Ch02-03. (실습) 작성한 지도 저장하기
---

 ### 작성한 지도 저장하기

 ```bash
 # bookstore world에 neuronbot2를 spawn하고 cartographer 수행 (이미 켜져있으면 skip)
 ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py
 ros2 launch neuronbot2_slam cartographer_launch.py open_rviz:=true use_sim_time:=true
 # 로봇 수동 제어
 ros2 run teleop_twist_keyboard teleop_twist_keyboard
 ```
 <div align="left">
   <img src="https://github.com/user-attachments/assets/0bb730a1-1cfa-46b1-9f23-1ab334c1691e" height="350" width="600">
  </div> 

 - cartographer를 작동시키고 로봇을 주행하여 아래 그림과 같이 지도 작성을 진행.

 ```bash
 cd ~/nav2_ws/src/neuronbot2/neuronbot2_nav/map
 ros2 run nav2_map_server map_saver_cli -f bookstore
 ```

 - Cartographer 등의 2D LiDAR 기반 SLAM 알고리즘을 통해 생성한 지도를 저장하려면 `nav2_map_server`

   패키지의 `map_saver` 노드를 실행해야 한다.
 - 지도를 저장할 디렉토리로 먼저 이동하면 그 위치에 지도를 저장할 수 있다.
   
   (`map_saver` 노드를 호출하기 전에 cartographer를 종료하면 생성한 맵을 잃게된다.)

 ```bash
 cd ~/nav2_ws/src/neuronbot2/neuronbot2_nav/map
 ros2 run nav2_map_server map_saver_cli -f bookstore
 ```
 <div align="left">
   <img src="https://github.com/user-attachments/assets/6fe736e0-a49a-4bc7-8f60-393e33151b14" height="350" width="600">
  </div> 
 
 - `*.pgm`파일
   - 이미지 파일로서 Occupancy Grid Map 기반의 지도 파일
 - `*.yaml` 파일
    - 지도의 메타데이터(metadata)가 포함된 속성 파일
    - **image:** 생성된 지도의 이미지가 포함된 파일 이름.
    - **mode:** 만들어진 지도의 영역을 3가지(점유된 영역, 비어있는 영역, 미지의 영역)로 구분할 것이라는 의미.

                => trinary를 사용.
    - **resolution:** 지도의 해상도(단위: m/pixel)
    - **origin:** 지도의 왼쪽 하단 2D 픽셀 좌표 (x, y, theta)
    - **ccupied_thresh:** 이 값보다 큰 픽셀은 점유 영역으로 간주함 (장애물로 표시됨)
    - **fresh_thresh:** 이 값보다 작은 값을 가진 픽셀은 완전히 비어있는 영역으로 간주
    - **negate:** 이 값이 '1'로 되어있을 경우 맵의 색상을 반전 ( 검정색 -free / 흰색 -occupied )

 ```bash
 cd ~/nav2_ws
 colcon build --symlink-install --packages-select neuronbot2_nav
 ```

 - 저장한 지도를 다음에 사용할 수 있도록, 빌드를 통해 워크스페이스의 install 디렉토리에 설치
                
## Ch02-04. 작성한 지도 수정 전략 및 다른 프로세스에서 활용 방법
---

 ### 작성한 지도 수정하기

  #### 작성한 지도를 수정하는 목적

   <div align="left">
   <img src="https://github.com/user-attachments/assets/c39e3cdf-52fa-4f6f-b2fc-5448893e5c98" height="350" width="600">
  </div> 

  - 아티팩트(artifact)
    -센서의 노이즈에 의해 생기는 점.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/ec696398-99d4-42a7-97e5-812947532a3d" height="350" width="600">
  </div> 

  - 리눅스 환경에서 포토샵을 이용한 작업이 제한 되므로 gimp 라는 에디터를 사용하여 지도의 장애물을 없앨 수 있다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/ef05cdf6-42f3-45ef-988f-913c1e9900b3" height="350" width="600">
  </div> 

  - 오픈소스로 제공되는 맵 수정 툴을 이용하여 격자 형태로 띄워진 맵을 수정할 수 있다.

 ### 저장한 맵을 다른 프로세스에서 사용하기 

  <div align="left">
   <img src="https://github.com/user-attachments/assets/ecbc2999-ea36-49c8-aadb-72fcd13c6b57" height="350" width="600">
  </div> 


  <div align="left">
   <img src="https://github.com/user-attachments/assets/303a8c0f-8b06-4edf-9fcf-0d6a8c45753d" height="350" width="600">
  </div> 
  
  - `map_server` 노드에서 `yaml_filename`을 파라미터로 받아서 토픽으로 map을 던져준다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/003795c7-59ad-4a20-b84f-db27552c2f92" height="350" width="600">
  </div> 
 
