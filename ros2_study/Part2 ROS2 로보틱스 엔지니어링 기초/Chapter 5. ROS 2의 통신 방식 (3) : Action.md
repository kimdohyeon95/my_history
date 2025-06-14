## Ch05-01 Action 개요 
---

 ### Action 이란? 

  <div align="left">
    <img src="https://github.com/user-attachments/assets/cf19f3a7-7e81-4372-8b1f-fa54c21a3195" height="350" width="700">
  </div>
  
  <div align="left">
    <img src="https://github.com/user-attachments/assets/820b47d5-6aa1-49df-b8a3-04ab97b06749" height="350" width="700">
  </div>

 ### Interface Type 정의: Action 

 <div align="left">
    <img src="https://github.com/user-attachments/assets/4ba13f61-cd99-4b07-9c50-4ab850104399" height="350" width="700">
  </div>

 ## Ch05-02. (실습) Action 명령어
 ---

  ### Action 필수 명령어 
  
   ```bash
   ros2 action -h
   ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/89152670-972d-493b-b8d7-d283d0af3f6a" height="350" width="700">
   </div>
  
   - action 관련 명령어 리스트를 보여준다. 

    
   #### list 
   
   ```bash
   ros2 action list
   ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/07706b81-1d36-4fcc-908d-6cbce382fdd0" height="350" width="700">
   </div>

   - 현재 ros2 시스템에서 사용 가능한 모든 액션 목록을 표시
   - 이렇게 액션들을 확인할 수 있는 이유는 시뮬레이션 환경을 열 때 액션 서버 노드들이 함께 켜졌기 때문이다.

   #### info 
   
   ```bash
   ros2 action info <action_name>
   ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/2c71590d-e78f-4ab7-a5ad-a8758a61ed77" height="200" width="450">
   </div>

   - 특정 액션에 대한 정보를 확인 할 때 사용
   - 액션 이름과 현재 실행되고 있는 Node 들에서 해당 액션을 사용하는 서버와 클라이언트 수를 표시.
   

   ```bash
   ros2 action info <action_name> -t
   ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/d3f7e619-2ec1-4a7d-9d8e-594182c1acbb" height="200" width="450">
   </div> 

   - 옵션 `-t`를 추가하면 사용된 인터페이스 타입에 대한 정보도 표시
   - 위 출력은 `/play_motion2`라고 하는 Action이 `play_motion2_msgs/action/PlayMotion2` 인터페이스를

     사용한다는 것을 알려준다.

   ```bash
   <pkg_name>/action/<interface_name>
   ```

   - 액션 인터페이스 구조는 위와 같이 되어있는데, `play_motion2_msgs`라는 패키지 안에 정의된 `PlayMotion2`라는

     인터페이스를 사용한다는 것을 알 수 있다. 

   ```bash
   ros2 interface show play_motion2_msgs/action/PlayMotion2
   ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/6ec923db-3b33-4467-80df-f2415a52b37d" height="350" width="550">
   </div> 

   - `ros2 interface show` 명령어로 인터페이스 정의 구조에 대해서도 알 수 있다.
   - 위와 같이 Action은 goal/result/feedback 세 부분으로 나누어져 있는 것을 알 수 있다. 

  #### send_goal 
  
  ```bash
  ros2 action send_goal <action_name> <action_type> <values>
  ```

  - `ros2 action send_goal` 명령어로 액션 서버에 Goal(요청)을 보낼 수 있다.
  -  위 명령어는 액션 클라이언트의 역할을 한다. 
  

  ```bash
  ros2 action send_goal /play_motion2 play_motion2_msgs/action/PlayMotion2 "{motion_name: 'wave'}"
  ```
  
  <div align="left">
     <img src="https://github.com/user-attachments/assets/a65bfacf-4198-46bf-b07e-1497b47d35fb" height="350" width="550">
   </div> 

 <div align="left">
     <img src="https://github.com/user-attachments/assets/80423d78-2b9b-42b2-ad33-328bcf42b23d" height="280" width="550">
 </div> 

 - tiago_gazebo 시뮬레이션 환경을 실행하여 백그라운드에서 실행되는 액션 서버들 중에서

   `play_motion2_msgs/action/PlayMotion2` 인터페이스 타입을 가진 `/play_motion2` 액션이 있다.
 - `ros2 action send_goal` 명령어로 `/play_motion2` 액션에 Goal을 요청하면

 - tiago 로봇의 로봇팔이 움직이는 동작과 함께 완료시 서버 측에 `Goal reached, success` 문장과 동시에

   클라이언트 측에 `Result:success` 가 날라가는 것을 볼 수 있다.   

  ```bash
  ros2 action send_goal -f /torso_controller/follow_joint_trajectory control_msgs/action/     FollowJointTrajectory "{trajectory: {joint_names: ['torso_lift_joint'], points: [{positions: [0.35], time_from_start: {sec: 3}}]}}"
  ```
<div align="left">
  <img src="https://github.com/user-attachments/assets/4b4f79be-53c4-456f-b771-24a0c502aaa1" height="280" width="550">
</div>

 - `ros2 action send_goal` 명령어에 `-f` 또는 `--feedback` 옵션을 붙이면 액션 동작 수행중에

   feedback 데이터를 모니터링 할 수 있다. 


  ```bash
  ros2 action send_goal /gripper_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['gripper_left_finger_joint', 'gripper_right_finger_joint'], points: [{positions: [0.01, 0.01], time_from_start: {sec: 2}}]}}"
  ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/68692dbd-f5df-4c53-a8b4-48129fae3ed3" height="350" width="550">
 </div>

 - `ros2 action send_goal` 명령어로 tiago 로봇의 gripper를 닫는 동작을 요청하면 시뮬레이션 환경에서

   gripper가 닫히는 동작을 수행하는 것을 볼 수 있다. 
  
  ```bash
  ros2 action send_goal /gripper_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['gripper_left_finger_joint', 'gripper_right_finger_joint'], points: [{positions: [0.04, 0.04], time_from_start: {sec: 2}}]}}"
  ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/d0132132-a1b2-4b4c-baa3-cc87ec0f831a" height="350" width="550">
 </div>

 - `ros2 action send_goal` 명령어로 tiago 로봇의 gripper를 여는 동작을 요청하면 시뮬레이션 환경에서

   gripper가 닫히는 동작을 수행하는 것을 볼 수 있다.

  ```bash
  ros2 action send_goal /head_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['head_1_joint', 'head_2_joint'], points: [{positions: [0.0, -0.5], time_from_start: {sec: 2}}]}}"
  ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/ffc453f8-e079-4471-b83b-a899a6595039" height="350" width="550">
 </div>

- `ros2 action send_goal` 명령어로 tiago 로봇의 고개를 숙이는 동작을 요청하면 시뮬레이션 환경에서

   고개를 숙이는 동작을 수행하는 것을 볼 수 있다.
  
  ```bash
  ros2 action send_goal /head_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['head_1_joint', 'head_2_joint'], points: [{positions: [0.0, 0.5], time_from_start: {sec: 2}}]}}"
  ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/d0b18b31-0d2c-46f5-9263-27afe9959891" height="350" width="550">
 </div>

 - `ros2 action send_goal` 명령어로 tiago 로봇의 고개를 드는 동작을 요청하면 시뮬레이션 환경에서

    로봇의 고개를 드는 동작을 수행하는 것을 볼 수 있다.  
 
  ```bash
  ros2 action send_goal /torso_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['torso_lift_joint'], points: [{positions: [0.35], time_from_start: {sec: 3}}]}}"
  ```
   <div align="left">
     <img src="https://github.com/user-attachments/assets/107a83a6-1810-4639-b9a2-6f8648439cfc" height="350" width="550">
 </div>

 - `ros2 action send_goal` 명령어로 tiago 로봇의 몸체를 올리는 동작을 요청하면 시뮬레이션 환경에서

    몸체를 올리는 동작을 수행하는 것을 볼 수 있다.
 
  ```bash
  ros2 action send_goal /torso_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory "{trajectory: {joint_names: ['torso_lift_joint'], points: [{positions: [0.0], time_from_start: {sec: 3}}]}}"
  ```
  <div align="left">
     <img src="https://github.com/user-attachments/assets/77acdfa0-179e-40db-b501-a42d81570368" height="350" width="550">
 </div> 

 - `ros2 action send_goal` 명령어로 tiago 로봇의 몸체를 낮추는 동작을 요청하면 시뮬레이션 환경에서

    몸체를 낮추는 동작을 수행하는 것을 볼 수 있다.
















