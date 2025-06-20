## Ch01-01. SLAM 개요 및 선수 지식 
---

 ### SLAM 이란?

 <div align="left">
  <img src="https://github.com/user-attachments/assets/3ddcaaf4-61f0-4ac4-b9f8-28183e27338e" height="350" width="600">
 </div>

  - **Simultaneous Localization And Mapping** 의 약자로 동시에 위치추정 및 지도작성을 하는 기술을 말한다.

  #### Localization 

  <div align="left">
   <img src="https://github.com/user-attachments/assets/10e7d586-8ae2-4ef5-991f-6ce5a11cbcf8" height="350" width="600">
  </div>

   - 지도가 주어진 상황에서 실제 주변 정보와 비교하여 내 위치 찾기.

  #### Mapping 

  <div align="left">
   <img src="https://github.com/user-attachments/assets/4037f6b6-5848-4d7b-90cb-c8a7e4855db3" height="350" width="600">
  </div>

  - 이동 정보가 주어진 상황에서 지도를 만드는 것이다. 
  - 내 위치 및 이동 정보를 알고 있고 주변 환경에 대한 지도를 생성하는 것이다.

  #### SLAM 
  
  <div align="left">
   <img src="https://github.com/user-attachments/assets/5745a602-cf14-4ae5-b792-74b2be9eddae" height="350" width="600">
  </div>

 ### Coordinates and Transformations

  #### 로봇의 현재 위치에서 문의 입구 중심까지 얼마나 떨어져 있나요?

  <div align="left">
    <img src="https://github.com/user-attachments/assets/a7ab8076-8dda-493a-b3da-fe212533a3df" height="350" width="600">
  </div>

  #### 2D Coordinate Frames 

  <div align="left">
    <img src="https://github.com/user-attachments/assets/850cb2c2-b2d7-483a-9baf-8bca7eae47cd" height="350" width="600">
  </div>

  - 로봇을 위에서 내려다 보았을 때, z축을 제외하고 x축은 로봇의 정면 방향 y축은 x축 기준 시계 반대 90도방향 이다.
  - x축 정면 방향이 (+) 반대편으로 가면 (-), y축은 x축 기준 시계 반대 90도 방향으로 갈수록 (+), 반대편은 (-) 이다.
  - 로봇의 중심 축을 기준으로 어느 위치 좌표를 나타 낼 수 있다. 

  #### 3D Coordinate Frames

  <div align="left">
    <img src="https://github.com/user-attachments/assets/34bc1de0-253f-481e-a69d-b0c587676765" height="350" width="600">
  </div>

  #### 2D LiDAR Data 

  <div align="left">
    <img src="https://github.com/user-attachments/assets/76c871f4-9747-438c-8111-bc7cff80fd46" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/ae01dbb5-679c-404e-aa42-1eb8378558f5" height="350" width="600">
  </div>

  - 위 그림 평면 좌표계에서 나타내져 있는 r 라이다 거리 데이터를 가지고, 라이다 각도 범위 angle_min

    ~ angle_max radian을 theta 각도로 변환하여 삼각함수 공식으로 (x,y) 형식의 2D 위치 좌표를 알아낼 수 있다.  

  #### 문 중앙까지의 위치 결정하기

  <div align="left">
    <img src="https://github.com/user-attachments/assets/32c28750-504c-49f8-bf9c-9e592a9c7a86" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/b90b63f2-73d0-4a99-bedc-cd28fae5f564" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/d9d8a759-94de-4847-9cae-08462c20ea06" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/5854fe9c-3cc8-45ab-b933-e1897297ad2f" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/e8cd85d1-aeb5-483f-9d4b-03cb2cca3d6d" height="350" width="600">
  </div>

  <div align="left">
    <img src="https://github.com/user-attachments/assets/1bb5f702-5622-483f-b5ae-25ca3d456b7d" height="350" width="600">
  </div>

  #### 로봇이 문을 통과하도록 이동시키기 

  <div align="left">
    <img src="https://github.com/user-attachments/assets/35af6825-5ea2-433f-aae6-8783271b7a50" height="350" width="600">
  </div>

  #### SLAM & Nav2에서의 필수 개념 - TF

  <div align="left">
    <img src="https://github.com/user-attachments/assets/d772d94b-6fdd-46fb-b996-4bb5ced626b7" height="350" width="600">
  </div>

  
