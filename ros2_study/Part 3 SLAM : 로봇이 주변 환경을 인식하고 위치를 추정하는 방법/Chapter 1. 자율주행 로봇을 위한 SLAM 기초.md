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

## Ch01-02 모바일 로봇을 위한 Odometry
---

 ### Odometry

  #### Odometry
 
  <div align="left">
    <img src="https://github.com/user-attachments/assets/34f319a5-9f35-48d2-b52a-e0865e692bcc" height="350" width="600">
  </div>
 
  - Wheel : 엔코더 달린 모터 
  - Inertial: IMU 센서 
  - Visual: 카메라

  #### 차동 구동 로봇 (Differential Drive Robot)
  
  <div align="left">
    <img src="https://github.com/user-attachments/assets/3264431d-ec39-45ad-a482-7f483b0d4d18" height="350" width="600">
  </div>
 
  - 초당 몇개의 엔코더가 카운트 되었는지 알게되면 바퀴가 얼마나 회전했는지 알 수 있다. 
 
  - 바퀴의 지름과 바퀴와 바퀴사이의 거리를 알고 있으면, 차동구동로봇의 Odometry 계산 가능. 
 
  - 바퀴의 지름이 영향을 미치는 것은 로봇의 이동거리가 되고 바퀴 사이의 거리는 회전량에 영향을 미친다.  

  #### 왜 Odometry가 자율주행에 있어 중요한 정보인가?
  
  <div align="left">
    <img src="https://github.com/user-attachments/assets/8da4894a-d18a-4610-bfde-1a1bce03cde3" height="350" width="600">
  </div>
 
  - Mapping 같은 경우는 Odometry가 로봇의 환경을 탐색하면서 주변의 물리적 구조를 바탕으로 지도를 만들어가는데 중요한 정보를 제공. 
 - Localization은 자신의 위치를 확정하거나 이미 만들어진 지도상에서 내 위치를 찾는 과정이다. 로봇이 시간이 지남에따라 이동한 거리,
 
   이동한 방향을 계산해서 현재 위치 추정에 사용되고, Odometry를 이용하여 지도가 있는 상황에서 얼마나 이동했을 때 어느 장애물이
 
   있는지를 잘 알 수 있다.
 - Navigation 시스템에서는 Odometry데이터를 기반으로 실시간 경로를 계속해서 조정한다. 
 - gps정보를 받을 수 없는 실내 환경에서 더욱 중요하게 작용하고, 로봇이 자신의 위치를 알고 있는 상황에서 목표지점 까지 거리와 방향을
 
   업데이트 해나갈 때 장애물을 회피하고 최적의 경로로 도달할 수 있도록 도와준다. 
 - 이와 관련하여 로봇의 동작을 정밀하게 제어하기 위해 Feedback Control을 해야할 때 위치 속도,방향 정보가 필요한데 이 때 Odometry가
 
   이러한 정보를 제공할 수 있다.

 ### 모바일 로봇에서 2D LiDAR가 주로 사용되는 이유

  #### Wheel Odometry의 단점

  <div align="left">
    <img src="https://github.com/user-attachments/assets/2b256b53-d950-4889-8081-3df4b51fff48" height="350" width="600">
  </div>

  - 휠 슬립 (wheel slip)
    - 바퀴가 지면을 완전히 접지하고 미끄러짐이 없다는 가정에 의존. 
    - 지면이 미끄럽거나 고르지 않은 상태일 때, 주행 시 1 바퀴를 회전할 때, 바퀴 둘레 만큼 이동하지 않는
    
      wheel slip이 발생하게 된다.
  - 주행에 따른 오차 누적
    - 로봇이 주행을 할 때, 1바퀴 회전할 때마다 주행명령 거리와 실제 주행 거리의 오차가 누적되어 발생한다.
    - 예를 들어 회전 오차가 누적 될 때, Ground Truth 그래프의 형태와 Odometry 로 저장한 그래프의 형태가 다르게 나타난다. 
    - 따라서 2D 라이다를 이용하여 주행거리와 상관없이 주변 환경에 대한 측정이 가능하기 때문에, Wheel Odometry에서

      발생한 오차를 보완해준다. 
  - 바퀴의 변형
    - 바퀴의 팽창과 같은 변형으로 인해 사전에 제공된 바퀴 둘레와 다르게 실제 주행거리가 기록된다. 

  #### 그럼 2D LiDAR 단독으로 2D LiDAR Odometry를 사용하면 되지 않나요?

  <div align="left">
    <img src="https://github.com/user-attachments/assets/e1584b85-fded-44d3-80cc-5f9b00fad90f" height="350" width="600">
  </div>

  - 특징이 부족한 환경 
    - 2D 라이다는 주변 환경에 대하여 레이저를 반사 할수 있는 물리적 특징을 이용한다. 
    - 그렇지만, 양옆으로 일직선인 복도처럼 특징이 부족한 환경에서는 기존 정보와 현재 정보가 같으므로

      이를 바탕으로 위치 추정 하기가 힘듬. 
  - Drift 문제 
   - 오랜 시간 동안 누적된 작은 오차가 큰 오차를 만든다. 
   - 특히 회전운동을 할 때, 라이다 데이터만으로 정확한 회전 각도를 구할 수 없다. 
  - 동적 환경에서의 문제 
    - 로봇은 가만히 있는데 주변 사람들이 이동함으로 써 노이즈 발생이 많기 때문에 로봇이 정적/동적 환경에 대한 구분을 못하게 된다.  

 ### 2D LiDAR 기반 알고리즘의 핵심

  #### ICP (Iterative Closest Point)

  <div align="left">
    <img src="https://github.com/user-attachments/assets/e39fcc8c-eef2-4c60-8933-33959e807a44" height="350" width="600">
  </div>

  - ICP 알고리즘은 연속적인 레이저 스캔을 반복적으로 정렬 해가면서 스캔 간의 차이를 최소화 함으로써 

    더 정확한 주행거리를 추정할 수 있다. 
  - 특히 기하학적 특징이 충분한 환경에 적합. 
  - Association
    - 한 포인트 클라우드 내의 각 포인트를 다른 포인트 클라우드의 가장 가까운 포인트와 연관을 지어서 매칭. 
    - 매칭을 통해서 포인트 클라우드간의 상관관계를 구축. 
    - 두 포인트 클라우드 간의 변환을 추정하는 기반을 마련하는 과정. 

  - Transformation 
    - Association 단계에서 매칭된 포인트들 사이의 최적의 기하학적 변환(회전, 이동)을 추정하게된다. 
    - source 포인트 클라우드를  target 포인트 클라우드와 정렬 하는데 사용하고 변환을 추정하는 방법으로 최소제곱법을

      사용하여 평균제곱 오차를 최소화하는 방향으로  rotation과 translation 행렬을 계산. 
  - Error Evaluation 
    - Transformation 단계에서의 수정된 변환을 이용하면 source 포인트 클라우드와  target 포인트 클라우드가 서로 맞춰도 오차가 발생하게 된다. 
    - 두 포인트 클라우드 간의 오차를 평가하고, 오류를 계산한 후, 오류를 최소화하는 방향으로 다시 앞의 단계를 진행. 





  
