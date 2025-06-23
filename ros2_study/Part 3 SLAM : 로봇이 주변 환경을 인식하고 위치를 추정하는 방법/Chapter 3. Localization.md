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
