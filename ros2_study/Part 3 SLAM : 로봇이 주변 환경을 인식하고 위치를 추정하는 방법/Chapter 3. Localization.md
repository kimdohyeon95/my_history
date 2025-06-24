## Ch03-01. Localization 개요
---

 ### Localization 

  <div align="left">
   <img src="https://github.com/user-attachments/assets/4454700e-19e5-4a0b-9e4e-9a806d8d235c" height="350" width="600">
  </div>

  <div align="left">
   <img src="https://github.com/user-attachments/assets/457208ed-8957-463f-a26b-929a5ddcd1f8" height="350" width="600">
  </div>

  <div align="left">
   <img src="https://github.com/user-attachments/assets/572ce601-18b1-4d4e-9b3e-e8c2f6da301c" height="350" width="600">
  </div>

  - Wheel Odometry 의 회전 오차가 누적되면 IMU 센서를 이용하여 보완 해준다. 
  
  <div align="left">
   <img src="https://github.com/user-attachments/assets/a8607ff5-8982-4c62-a954-c4a457352a45" height="350" width="600">
  </div>

  
- map 프레임과 odom 프레임과의 관계를 알 수 있고, odom 프레임과 base_link 프레임과의 관계를 알 수 있으므로

  결국 map을 기준으로 로봇이 어디에 있는지를  알 수 있다. 
- odom 프레임과 base_link 프레임 사이의 생겨난 위치 오차를 localization 노드가 map 프레임과 odom 프레임 둘과의 관계를

  조정 해줌으로써, map 기준으로 로봇의 정확한 위치를 표현할 수 있다. 


 <div align="left">
  <img src="https://github.com/user-attachments/assets/fa00ec39-1c93-4c76-b5c1-2d62e917be48" height="350" width="600">
 </div>

 - 로봇의 위치와 실제 위치가 맞지 않은 경우, amcl 노드가 센서 정보와 지도 정보를 바탕으로 환경의 특징을 가지고

    내가 어디에 있는지를 오차를 줄이는 방향으로 보정을 진행한다. 

 ### 2D LiDAR 기반의 Localization Package

 <div align="left">
  <img src="https://github.com/user-attachments/assets/ed7d9275-f953-42af-9990-66c58c04b6b6" height="350" width="600">
 </div>
 
- 라이다와 같은 센서 값을 통해서 주변환경을 관측할 때, 맵과 잘 일치 할 수 있도록 하는 확률이 높은 파티클들을 유지하고

  가능성이 낮은 것들은 점점 버린다. 

- 로봇이 이동하면 할 수록 이동량과 취득한 센서값을 바탕으로 내가 지도상에서 어느곳에 위치할 가능성이 높은지를

  점점 수렴하게 하면서 최종적으로 지도상에서 로봇이 어디있는지를 알 수 있다.

## Ch03-02. (실습) AMCL (Adaptive Monte Carlo Localization)
---

 ### AMCL 수행을 위한 준비

  #### Launch 파일

  ```bash
    ...
  
  Node(
      package='nav2_map_server',
      executable='map_server',
      name='map_server',
      output='screen',
      respawn=use_respawn,
      respawn_delay=2.0,
      parameters=[configured_params],
      remappings=remappings),
  Node(
      package='nav2_amcl',
      executable='amcl',
      name='amcl',
      output='screen',
      respawn=use_respawn,
      respawn_delay=2.0,
      parameters=[configured_params],
      remappings=remappings),
  Node(
      package='nav2_lifecycle_manager',
      executable='lifecycle_manager',
      name='lifecycle_manager_localization',
      output='screen',
      parameters=[{'use_sim_time': use_sim_time},
                  {'autostart': autostart},
                  {'node_names': lifecycle_nodes}])
  
  ...
  ```

  - `~/nav2_ws/src/neuronbot2/neuronbot2_nav/launch/localization_launch.py` 에 위에서 언급되었던 세 가지 노드가 사용
  - `nav2_map_server`: 실제 map yamal 파일을 파라미터로 받아서 map을 제공
  - `nav2_amcl`: 실제 localization 알고리즘을 수행하는 노드.
  - `nav2_lifecycle_manager`: localization 수행과 관련된 노드들을 관리하는 역할 파리미터로 관리할 노드이름을 전달받는다.  

  ```bash
  my_nav_dir = get_package_share_directory('neuronbot2_nav')
  my_map_dir = os.path.join(my_nav_dir, 'map')
  my_map_file = 'bookstore.yaml'
  
  ...
  
  map_yaml_file = LaunchConfiguration('map')
  
  ...
  
  param_substitutions = {
      'use_sim_time': use_sim_time,
      'yaml_filename': map_yaml_file}
  
  configured_params = RewrittenYaml(
      source_file=params_file,
      root_key=namespace,
      param_rewrites=param_substitutions,
      convert_types=True)
  
  ...
  
  declare_map_yaml_cmd = DeclareLaunchArgument(
      'map',
      default_value=os.path.join(my_map_dir, my_map_file),
      description='[localize] Full path to map yaml file to load')
  ```

  - map_server는 위의 코드로부터 지도의 메타 파일(*.yaml)을 읽어 지도 정보를 불러올 수 있다.

  ```bash
  my_nav_dir = get_package_share_directory('neuronbot2_nav')
  my_param_dir = os.path.join(my_nav_dir, 'param')
  my_param_file = 'neuronbot_params.yaml'
  
  ...
  
  params_file = LaunchConfiguration('params_file')
  
  ...
  
  configured_params = RewrittenYaml(
      source_file=params_file,
      root_key=namespace,
      param_rewrites=param_substitutions,
      convert_types=True)
  
  ...
  
  declare_params_file_cmd = DeclareLaunchArgument(
      'params_file',
      default_value=os.path.join(my_param_dir, my_param_file),
      description='Full path to the ROS2 parameters file to use')
  ```

  - amcl은 위의 코드로부터 yaml 파일을 읽어 필요한 파라미터들을 불러올 수 있다.

  ```bash
  lifecycle_nodes = ['map_server', 'amcl']
  ```

  - lifecycle_manager가 관리해야 하는 노드의 이름이 포함된 리스트를 사전에 정의. 

  #### YAML 파일 
  
  ```bash
  amcl:
  ros__parameters:
    use_sim_time: False
    alpha1: 0.9
    alpha2: 0.1
    alpha3: 0.05
    alpha4: 0.01
    alpha5: 0.04
    base_frame_id: "base_footprint"
    beam_skip_distance: 0.5
    beam_skip_error_threshold: 0.9
    beam_skip_threshold: 0.3
    do_beamskip: false
    global_frame_id: "map"
    lambda_short: 0.1
    laser_likelihood_max_dist: 2.0
    laser_max_range: 100.0
    laser_min_range: -1.0
    laser_model_type: "likelihood_field"

    ...
  ```

  - 위에서 언급된 경로(`~/nav2_ws/src/neuronbot2/neuronbot2_nav/param`)에는 `neuronbot_params.yaml` 파일이 있고 amcl 블럭에

    localization과 관련된 파라미터들이 정의되어있다.

  #### Rviz 파일
  
  ```bash
  cd ~/nav2_ws/src/neuronbot2/neuronbot2_nav/rviz
  rviz2 -d nav2_default_view.rviz
  ```

  - 설정 파일 수정을 위해 기존의 rviz 파일을 열어준다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/74e7943f-6d3a-4291-b842-2334697b3e0d" height="400" width="450">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/ac564fa4-5c2f-4441-81c4-f88dedf90032" height="350" width="450">
  </div>

  - Rviz 시각화 툴을 켜고, 디스플레이 패널에서 ParticleCloud 타입을 추가한 후 topic을 /particle_cloud`로 지정하면

    amcl 노드가 localization을 진행할 때 쓰이는 파티클이 생성된다.
  - Topic 하위 메뉴에서 Reliable Policy 값을 Best Effort로 지정해야 파티클이 정상적으로 시각화된다.
  - `ctrl + s`를 눌러 설정을 저장해.

 ### AMCL을 통한 Localization 실습
 
 ```bash
 ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py 
 ```

 - 시뮬레이션 환경(bookstore)에 neuronbot2을 spawn

 <div align="left">
    <img src="https://github.com/user-attachments/assets/465fd729-6db1-4414-8002-c5aba2a2f0db" height="400" width="500">
 </div>

 ```bash
 ...

 def generate_launch_description():
     # Get the launch directory
     my_nav_dir = get_package_share_directory('neuronbot2_nav')
     my_param_dir = os.path.join(my_nav_dir, 'param')
     my_param_file = 'neuronbot_params.yaml'
     my_map_dir = os.path.join(my_nav_dir, 'map')
     my_map_file = 'bookstore.yaml'
     
 ...
 ```

 - 사용할 지도의 속성 파일을 불러올 수 있도록 `my_map_file` 변수의 값을 `bookstore.yaml`로 수정.

 ```bash
 ros2 launch neuronbot2_nav localization_launch.py use_sim_time:=true
 ```

 - AMCL 기반의 Localization 수행을 위해 아래 런치 파일을 시작.

 ```bash
 cd ~/nav2_ws/src/neuronbot2/neuronbot2_nav/rviz
 rviz2 -d nav2_default_view.rviz
 ```

 - Rviz2를 실행하여 Localization 상황을 확인.

 ```bash
 ros2 run teleop_twist_keyboard teleop_twist_keyboard
 ```

 - 로봇을 키보드로 제어하여 Localization이 제대로 수행되는지 관찰.

 <div align="left">
   <img src="https://github.com/user-attachments/assets/8014e288-dad2-4640-820b-8144fe826d09" height="400" width="700">
  </div>
 
 - 지도에서 로봇의 초기 위치를 설정하기 위해 `2D Pose Estimate` 버튼을 클릭한 후, 시뮬레이터 상에서

   로봇의 실제위치와 해당되는 비슷한 위치와 방향을 클릭 해준다.
 - 그 후, 키보드로 로봇을 움직여 AMCL이 새 로봇 위치에 어떻게 적응하는지 관찰하고, 가능성이 높은 로봇 위치에

   파티클이 집중되면서 Localization에 성공하는 것을 알 수 있다.
 - 이를 통해, amcl 알고리즘에 있어서 초기값은 중요하고, 대략적인 위치와 방향이 맞아 떨어져야 주변 환경에 대한

   센서 정보와 map 정보를 기반으로 정확한 위치를 찾을 가능성이 높아진다. 
