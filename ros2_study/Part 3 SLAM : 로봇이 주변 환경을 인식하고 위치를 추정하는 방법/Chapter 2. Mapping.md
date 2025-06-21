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


