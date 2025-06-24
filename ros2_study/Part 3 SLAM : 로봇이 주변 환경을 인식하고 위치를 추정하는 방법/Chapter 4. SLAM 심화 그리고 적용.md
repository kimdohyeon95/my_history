## Ch04-01. SLAM 파리미터 튜닝 전략
---

 ### [Mapping] Cartographer 파라미터 튜닝

 - 최상의 지도 결과를 얻으려면 Cartographer에 대한 설정을 올바르게 구성해야 한다. 모든 설정은 Lua 파일에서 지정할 수 있다.
 - Cartographer의 입력으로 들어가는 Topic 이름은 기본적으로 아래와 같이 정해져있다.
   - 2D LiDAR Topic (sensor_msgs/msg/LaserScan) : `/scan`
   - Odometry Topic (nav_msgs/msg/Odometry) : `/odom`
   - IMU Topic (sensor_msgs/msg/Imu) : `/imu`
 - 위 토픽 이름과 일치하지 않는다면 launch 파일 내  remapping을 통해 토픽의 이름을 Cartographer에 넘겨줄 수 있습니다.

 ```bash
 ...

  Node(
      package='cartographer_ros',
      executable='cartographer_node',
      name='cartographer_node',
      output='screen',
      parameters=[{'use_sim_time': use_sim_time}],
      remappings=[
  		    ('scan', 'custom_scan_topic_name'),  # 2D LiDAR data
  		    ('odom', 'custom_odom_topic_name')   # Odometry data
  		    ('imu', 'custom_imu_topic_name'),    # IMU data
  		],
      arguments=[
          '-configuration_directory', cartographer_config_dir,
          '-configuration_basename', configuration_basename]),
       
 ...
 ```

 - 토픽 이름과 일치하지 않는다면 launch 파일 내 remapping을 통해 토픽의 이름을 Cartographer에 넘겨줄 수 있다.

  #### General Parameters

  - `map_frame`
    - 맵 publish를 위한 frame ID
    - odom_frame의 parent frame으로 사용되며, 일반적으로 `map` 이라는 이름으로 설정
  - `tracking_frame`
    - SLAM 알고리즘이 추적하고자 하는 frame ID
    - 일반적으로 `base_link` 또는 `base_footprint`로 설정
    - IMU를 사용하는 경우 IMU frame ID로 설정해야함 (ex. `imu_link`)
  - `published_frame`
    - 로봇 위치를 publish하는 데 사용되는 frame ID
    - `map_frame`으로부터 odom의 위치가 publish 된다.
    - 예를 들어, wheel odometry로부터 odom frame이 제공되는 경우 `odom`을 사용
  - `odom_frame`
    - `provide_odom_frame`이 true인 경우에만 사용된다.
    - `published_frame`과 `map_frame` 사이에 사용되어 로컬 SLAM 결과(루프 클로징이 적용되지 않은)를 발행하는 frame

      (일반적으로 `odom`이라는 이름으로 설정)
  - `provide_odom_frame`
    - 활성화되면, 연속적인 위치를 `map_frame`에서 `odom_frame`으로 발행

  - `use_odometry`
    - 활성화되면 nav_msgs/Odometry 타입의 `odom` 토픽에 대해 subscribe함
    - 오도메트리 정보를 제공받을 수 있으며, 이 정보는 SLAM 알고리즘에 사용된다.
  - `use_nav_sat`
    - 활성화되면 sensor_msgs/NavSatFix 타입의 `fix` 토픽에 대해 subscribe함
    - GNSS 정보를 제공받을 수 있으며, 이 정보는 Global SLAM 알고리즘에 사용된다.

  #### Sensor Parameters

  - `num_laser_scans`
    - subscribe할 2D LiDAR의 개수
      - 하나의 2D LiDAR일 경우, sensor_msgs/LaserScan 타입의 `scan` 토픽을 subscribe
      - 여러개의 2D LiDAR일 경우, `scan_1`, `scan_2` 등의 토픽 이름을 subscribe
  - `num_point_clouds`
    - subscribe할 포인트 클라우드의 개수 (ex. 3D LiDAR, Depth Sensor)
      - 하나의 포인트 클라우드일 경우, sensor_msgs/PointCloud2 타입의 `points2` 토픽을 subscribe
      - 여러개의 포인트 클라우드일 경우, `points2_1`, `points2_2` 등의 토픽 이름을 subscribe

  #### Filter Parameters

  - `lookup_transform_timeout_sec`
    - tf2를 사용하여 TF를 조회하는 데 사용되는 타임아웃 (단위: 초)
  - `submap_publish_period_sec`
    - 맵을 publish하는 주기 (단위: 초)
  - `pose_publish_period_sec`
    - 로봇 위치를 publish하는 주기 (단위: 초)
  - `trajectory_publish_period_sec`
    - trajectory marker를 publish하는 주기 (단위: 초)
  - `rangefinder_sampling_ratio`
    - 거리 측정을 위한 센서(2D LiDAR 등) 데이터의 샘플링 비율
    - 1.0일 경우 모든 센서데이터를 사용 / 0.5일 경우 절반만 사용하여 처리시간을 줄인다.
  - `odometry_sampling_ratio`
    - 오도메트리 데이터의 샘플링 비율
  - `fixed_frame_sampling_ratio`
    - 고정 프레임 데이터의 샘플링 비율
  - `imu_sampling_ratio`
    - IMU 센서 데이터의 샘플링 비율

  #### TRAJECTORY_BUILDER Parameters

  - `TRAJECTORY_BUILDER_2D.min_range`
    - 맵 구축에 고려될 최소 측정 거리 (이 값보다 짧은 거리의 데이터는 무시)
    - 센서 노이즈나 매우 가까운 물체로 인한 잘못된 데이터를 필터링하는 데 사용
  - `TRAJECTORY_BUILDER_2D.max_range`
    - 맵 구축에 고려될 최대 측정 거리 (이 값보다 긴 거리의 데이터는 무시)
    - 센서의 최대 유효 범위를 넘어서는 거리 데이터를 제거하여 처리 효율을 높이고, 잘못된 데이터로 인한 오류를 줄이는 데 사용

  #### 동적 파라미터 튜닝 






  ![image](https://github.com/user-attachments/assets/b60b23b6-b115-4398-99b0-e5fb1a11f232)
