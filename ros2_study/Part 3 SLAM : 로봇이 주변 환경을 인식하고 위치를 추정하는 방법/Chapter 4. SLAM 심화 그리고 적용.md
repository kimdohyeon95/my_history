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

  <div align="left">
   <img src="https://github.com/user-attachments/assets/b60b23b6-b115-4398-99b0-e5fb1a11f232" height="400" width="700">
  </div>

  - 동적 파라미터 튜닝을 지원하는 패키지의 경우, `rqt`의 `dynamic reconfigure`를 사용하여 실행 중인 시스템의 파라미터를 실시간으로 변경할 수 있다.

    즉, 파라미터 변경을 위해 해당 시스템을 재시작할 필요가 없다.
  - 또한, 다양한 설정을 신속하게 실험해볼 수 있으므로, 최적의 파라미터를 찾는 과정이 훨씬 빨라진다. 이는 특히 로봇이 다양한 환경 조건이나 임무를

    수행해야 할 때 유용하다.

 ### [Localization] AMCL 파라미터 튜닝

 - AMCL에 대한 모든 설정은 `yaml` 파일에서 지정할 수 있다.
   - AMCL 패키지는 nav2에서 포함되기 때문에 파라미터들은 nav2 설정파일 내에서 같이 관리된다.
   - 실습 환경에서는 `~/nav2_ws/src/neuronbot2/neuronbot2_nav/param`의 `neuronbot_params.yaml` 파일에 AMCL 파라미터가 정의되어있다.
 - 2D Localization의 경우 map 프레임을 기준으로 로봇의 위치 (x,y,theta)가 표현된다.

   <div align="left">
    <img src="https://github.com/user-attachments/assets/d711d033-e38c-43c8-ac7d-439a0b49e921" height="150" width="300">
   </div>

  - x: `map` 프레임으로부터 로봇의 x 좌표
  - y: `map` 프레임으로부터 로봇의 y 좌표
  - theta: 'map` 프레임으로부터 로봇의 방향

  #### Overall Filter Parameters

  - `min_particles` (int, 기본값: 500)
    - 사용되는 최소 파티클 수 (너무 적은 파티클 수는 위치 추정의 정확성을 떨어뜨릴 수 있다)
  - `max_particles` (int, 기본값: 2000)
    - 사용되는 최대 파티클 수 (너무 많은 파티클 수는 계산 부하를 증가)
  - `update_min_d` (double, 기본값: 0.25미터)
    - 필터 업데이트를 수행하기 전 필요한 최소 이동 거리 (불필요한 업데이트를 줄여 성능을 최적화)
  - `update_min_a` (double, 기본값: 0.2라디안)
    - 필터 업데이트를 수행하기 전 필요한 최소 회전량 (회전에 따른 위치 추정의 정확도를 높인다)
  - `resample_interval` (int, 기본값: 1)
    - 재샘플링을 수행하기 전 필요한 필터 업데이트 횟수 (적절한 재샘플링 주기는 필터의 효율성을 높인다)
  - `transform_tolerance` (double, 기본값: 1.0초)
    - Publish된 TF(transform)가 유효하다고 표시되는 시간 (동기화 오류를 방지하고, 데이터의 정확성을 유지)
  - `recovery_alpha_slow` (double, 기본값: 0.0 (비활성화))
    - 위치 추정 실패 시 로봇이 회복할 수 있는 능력을 결정
  - `recovery_alpha_fast` (double, 기본값: 0.0 (비활성화))
    - recovery_alpha_slow와 유사하지만, 회복을 더 빠르고 강력하게 만들어 준다
  - `set_initial_pose` (bool, 기본값: false)
    - 초기 자세를 initial_pose 파라미터로부터 설정
    - 로봇이 처음 시작할 때 정확한 위치에서 시작할 수 있게 한다.
  - `initial_pose` (Pose2D, {0.0, 0.0, 0.0})
    - 로봇 베이스 프레임의 초기 자세(X, Y, Z 좌표 및 yaw)
    - 정확한 초기 위치 설정이 위치 추정의 기준점을 제공
  - `always_reset_initial_pose` (bool, 기본값: false)
    - AMCL이 초기 자세를 토픽 또는 `initial_pose` 파라미터를 통해 받도록 요구
    - 재시작 시 정확한 초기 자세를 사용하여 위치 추정의 정확성을 유지
  - `save_pose_rate` (double, 기본값: 0.5 Hz)
    - 추정된 최종 자세와 공분산을 파라미터 서버에 저장하는 최대 속도
    - 이전 실행에서의 위치를 기억하고, 재시작 시 이를 사용하여 위치 추정을 초기화

  #### Laser Model Parameters

  - 어떤 혼합 가중치를 사용하든 합이 1이 되어야 한다.
    - 예를 들어, 빔 모델에서는 z_hit, z_short, z_max 및 z_rand의 4개를 모두 사용
    - 반면 `likelihood_field` 모델은 z_hit와 z_rand의 2개만 사용
  - `laser_min_range` (double, 기본값: -1.0)
    - 고려될 최소 스캔 범위로 -1.0을 설정하면 레이저가 보고하는 최소 범위를 사용
    - 너무 가까운 장애물을 제외시켜 불필요한 노이즈를 줄인다.
  - `laser_max_range` (double, 기본값: 100)
    - 고려될 최대 스캔 범위로 -1.0을 설정하면 레이저가 보고하는 최대 범위를 사용
    - 먼 거리의 장애물을 고려하여 로봇의 환경 인식을 개선
  - `laser_likelihood_max_dist` (double, 기본값: 2.0미터)
    - `likelihood_field` 모델 사용 시 맵에 장애물 팽창을 수행할 최대 거리
    - 로봇 주변의 공간을 현실적으로 모델링하여 위치 추정의 정확도를 높인다.
  - `laser_model_type` (string, 기본값: "likelihood_field")
    - 사용할 레이저 모델의 유형 (beam, likelihood_field, likelihood_field_prob 중 선택 가능)
    - 모델 선택은 환경 인식의 정확성과 시스템의 효율성에 직접적인 영향을 미친다.

  #### Odometry Model Parameters

  - `robot_model_type` (string, 기본값: "differential")
    - 사용할 로봇 모델의 유형
      - "differential" (차동 드라이브 모델)
      - "omnidirectional" (전방향 드라이브 모델)
  - `alpha1` (double, 기본값: 0.2)
    - 로봇의 회전 움직임에서 발생하는 오도메트리의 회전 추정 노이즈를 지정
    - 회전 중 발생할 수 있는 오류를 예측하여 보정함으로써, 위치 추정의 정확도를 높인다.
  - `alpha2` (double, 기본값: 0.2)
    - 로봇의 이동 중 발생하는 오도메트리의 회전 추정 노이즈를 지정
    - 이동 중에 회전으로 인해 발생하는 오류를 정량화하고 이를 통해 위치 추정을 보정
  - `alpha3` (double, 기본값: 0.2)
    - 로봇의 이동에서 발생하는 오도메트리의 이동 추정 노이즈를 지정
    - 이동 시 발생할 수 있는 오류를 보정하여 위치 추정의 정확성을 향상
  - `alpha4` (double, 기본값: 0.2)
    - 로봇의 회전 중 발생하는 오도메트리의 이동 추정 노이즈를 지정
    - 회전 동작 중 발생할 수 있는 이동 오류를 정량화하고 보정
  - `alpha5` (double, 기본값: 0.2)
    - omnidirectional 모델에서 사용되는 이동 관련 노이즈 파라미터
    - omnidirectional 모델 특성상 다양한 방향으로의 이동에서 발생할 수 있는 노이즈를 고려하여 위치 추정의 정확도를 보장
  - `odom_frame_id` (string, 기본값: "odom")
    - 오도메트리 데이터에 사용되는 프레임의 ID
  - `base_frame_id` (string, 기본값: "base_footprint")
    - 로봇 베이스에 사용되는 프레임의 ID
  - `global_frame_id` (string, 기본값: "map")
    - 전역 위치 참조 프레임으로서, 모든 위치 추정과 지도 데이터의 기준점 역할
  - `tf_broadcast` (bool, 기본값: true)
    - AMCL이 글로벌 프레임과 오도메트리 프레임 사이의 TF를 publish할지 여부
    - 필요에 따라 이 기능을 비활성화하여 데이터 통신 부하를 줄이거나 시스템 간 상호 작용을 제어할 수 있다.

## Ch04-02. (실습) AMCL 기반의 로봇 초기 위치 추정 전략
---

 ### AMCL 기반의 로봇 초기 위치 추정

 - AMCL 기반으로 Localization을 수행할 때 초기 위치를 정해줘야 한다. 지금까지는 `Rviz2`를 사용하여 이 작업을 수행하였지만,

   초기 위치 설정을 자동으로 할 수 있는 방법에 대해 알아본다.

  #### [방법1] YAML 파일에서 초기 위치 설정하기

  ```bash
  amcl:
  ros__parameters:
		...

    # Initial Pose
    set_initial_pose: True
    initial_pose.x: 5.0
    initial_pose.y: 5.0
    initial_pose.z: 0.0
    initial_pose.yaw: -3.141592
  ```

  - `~/nav2_ws/src/neuronbot2/neuronbot2_nav/param`경로의 `neuronbot_params.yaml` 파일을 아래와 수정.
  
  <div align="left">
   <img src="https://github.com/user-attachments/assets/b60b23b6-b115-4398-99b0-e5fb1a11f232" height="400" width="700">
  </div>


  ```bash
  # 시뮬레이션 환경 (Terminal 1)
  ros2 launch neuronbot2_gazebo neuronbot2_world.launch.py
  
  # Rviz2 실행 (Terminal 2)
  cd ~/nav2_ws/src/neuronbot2/neuronbot2_nav/rviz
  rviz2 -d nav2_default_view.rviz
  
  # Localization (Terminal 3)
  ros2 launch neuronbot2_nav localization_launch.py use_sim_time:=true
  ```

  - 런치 파일을 다시 실행시키고 결과를 확인

  <div align="left">
   <img src="https://github.com/user-attachments/assets/e6681681-b1ce-443e-882b-96670697f995" height="350" width="450">
  </div>

  -로봇의 위치가 x: 5.0, y: 5.0 원래 위치 기준 -180도 방향으로 위치해 있는 것을 확인 할 수 있다. 

  #### [방법2] 터미널에서 초기 위치 설정하기

  - AMCL 노드는 원하는 로봇의 초기 포즈를 게시할 수 있는 토픽을 제공한다. `/initialpose` 토픽을 통해 초기 위치를 설정 할 수 있다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/259babe6-c31f-4d9b-b3a1-e9a1b758cf35" height="30" width="450">
  </div>

  - Rviz2 상의 `Publish Point` 버튼을 통해 초기 위치를 잡을 좌표가 어디인지 확인할 수 있다. 버튼을 누른 뒤 지도 상에서 특정 위치를 누르면

    `/clicked_point` 토픽이 publish 되는 것을 `ros2 topic echo` 명령어로 확인할 수 있다.

  ```bash
  ros2 topic echo /clicked_point
  ```

  <div align="left">
   <img src="https://github.com/user-attachments/assets/69ba3ff1-a0f9-4945-a9dc-c2d0136de20a" height="300" width="450">
  </div>

  ```bash
  ros2 topic pub -1 /initialpose geometry_msgs/msg/PoseWithCovarianceStamped "{header: {stamp: {sec: 0}, frame_id: 'map'}, pose: {pose: {position: {x: 5.0, y: 0.0, z: 0.0}, orientation: {w: 1.0}}}}"
  ```
  - 위 명령어로 `/initialpose` 토픽을 퍼블리싱하여 초기 위치를 설정 한다.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/d81ea845-c9e6-48f7-81b0-8e358332a477" height="350" width="800">
  </div>

  - 설정한 좌표인 위치 (x: 5.0, y: 0.0, z: 0.0), 회전 (x: 0.0, y: 0.0, z: 0.0, w: 1.0)으로 로봇 위치가 초기화된 것을 확인할 수 있다.

  #### [방법3] 프로그램 상에서 초기위치 설정하기

  - 완전 자율주행 로봇을 구현하려는 경우 로봇을 켤 때마다 터미널을 통해 로봇의 초기화를 수행하는 것을 원하지 않는다. 이를 방지하기 위해

    [방법2]에서 언급했던 `/initialpose` 토픽을 활용해 초기 위치를 프로그램 상에서 정해줄 수 있다.

  ```bash
  sudo apt install ros-humble-tf-transformations

  cd ~/nav2_ws/src
  ros2 pkg create --build-type ament_python localizer_server --dependencies rclpy geometry_msgs tf-transformations
  ```

  - `nav2_ws/src` 디렉터리에 `localizer_server`라는 이름의 새 패키지를 만들고 토픽 작업에 필요한 종속성을 추가.
  - `geometry_msgs/msg/PointStamped`, `geometry_msgs/msg/PoseWithCovarianceStamped` 등의 인터페이스가 사용될 것이 때문에

    `geometry_msgs`를 종속성으로 추가

  ```bash
  import rclpy
  from rclpy.node import Node
  from geometry_msgs.msg import PoseWithCovarianceStamped
  from geometry_msgs.msg import PointStamped
  from tf_transformations import quaternion_from_euler
  
  # init_pose = x, y, theta
  init_pose = [3.0, 4.0, 3.141592]
  
  class InitRobot(Node):
  
      def __init__(self):
          super().__init__('initial_pose_pub_node')
          self.init_pose_pub_ = self.create_publisher(PoseWithCovarianceStamped, '/initialpose', 1)
          self.clicked_point_sub_ = self.create_subscription(PointStamped, '/clicked_point', self.point_callback, 1)
  
          # Set initial pose after a short delay
          timer_period = 0.5  # seconds
          self.trial_count = 5
          self.timer = self.create_timer(timer_period, self.timer_callback)
  
      def timer_callback(self):
          self.trial_count -= 1
          self.init_pose(init_pose[0], init_pose[1], init_pose[2])
  
          if self.trial_count == 0:
              self.timer.cancel()  # Cancel timer after firing once
  
      def point_callback(self, msg):
          self.get_logger().info('Recieved Data:\n X : %f \n Y : %f \n Z : %f' % (msg.point.x, msg.point.y, msg.point.z))
          self.init_pose(msg.point.x, msg.point.y)
  
      def init_pose(self, x, y, theta=0.0):
          # radian to quaternion
          quat = quaternion_from_euler(0.0, 0.0, theta)
  
          # Publish initial pose
          msg = PoseWithCovarianceStamped()
          msg.header.frame_id = '/map'
          msg.pose.pose.position.x = x
          msg.pose.pose.position.y = y
          msg.pose.pose.position.z = 0.0
          msg.pose.pose.orientation.x = quat[0]
          msg.pose.pose.orientation.y = quat[1]
          msg.pose.pose.orientation.z = quat[2]
          msg.pose.pose.orientation.w = quat[3]
  
          self.get_logger().info('Publishing  Initial Position\n X= %f \n Y= %f '% (msg.pose.pose.position.x, msg.pose.pose.position.y))
          self.init_pose_pub_.publish(msg)
  
  def main(args=None):
      rclpy.init(args=args)
      init_robot = InitRobot()
  
      rclpy.spin(init_robot)
      init_robot.destroy_node()
      rclpy.shutdown()
  
  if __name__ == '__main__':
      main()
  ```

  - 방금 생성한 패키지의 `localizer_server` 디렉터리에 `init_robot.py`라는 새 파일을 생성
  - `InitRobot` 클래스
    - `/initpose` 토픽 이름의 `PoseWithCovarianceStamped` 인터페이스 타입을 가지는 `init_pose_pub_` 퍼블리셔 생성.
    - '/clicked_point' 토픽 이름의 `PointStamped` 인터페이스 타입을 가지는 `clicked_point_sub_` 구독 생성.
  - `timer_callback`함수
    - ROS1 에서 프로그램 코드 상으로 topic 을 publish 하여 초기 위치를 지정하면 한번에 초기화가 안되는 문제가 존재.
    - 초기 위치를 `trial_count` 변수의 값 만큼 publish 하여 초기화를 제대로 수행하기 위함이다.
  - `point_callback`함수
    - rviz2의 `Publish Point` 버튼으로 지도상의 위치를 클릭했을 때, 발행되는 `/clicked_point` 토픽을 받기 위함이다.
  - `init_pose`함수
    - rviz2의 `2D Pose Estimate` 버튼으로 로봇의 위치를 초기화하는 기능을 구현하기 위해 인자로 받은 x,y,theta 위치 좌표를

      인자로 받아서 theta각을 쿼터니언으로 변환 후 `PoseWithCovarianceStamped` 타입으로 publish 하여 로봇 위치 초기화 수행.  

  ```bash
  entry_points={
      'console_scripts': [
          'init_pose = localizer_server.init_robot:main',
      ],
  },
  ```

  - `setup.py`를 수정하여 `init_robot.py` 스크립트의 실행 파일을 `entry_points`에 추가

  ```bash
  cd ~/nav2_ws
  colcon build --symlink-install --packages-select localizer_server
  source ~/nav2_ws/install/local_setup.bash
  ```

  - 워크스페이스 루트 디렉토리로 이동하여 패키지를 빌드.

  ```bash
  ros2 run localizer_server init_pose
  ```

  - `localizer_server` 노드를 실행시켜 설정한 초기 위치대로 로봇 위치가 설정되는지 확인.

  <div align="left">
   <img src="https://github.com/user-attachments/assets/f70bd790-946b-4bca-a230-062b7d0c2414" height="400" width="700">
  </div>
  



