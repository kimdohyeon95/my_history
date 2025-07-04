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

## Ch05-03. (실습) Action Programming (1) - Client
---

 ### Action Client Node 

 - 목표
   - `play_motion2_msgs/action/PlayMotion2` 타입의 `/play_motion2` 액션을 호출하는

      액션 클라이언트 노드 생성

 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True 
 ```

 - tiago_gazebo 시뮬레이션 환경 실행. 

 ```bash
 ros2 pkg create --build-type ament_python tutorial_action --dependencies rclpy play_motion2_msgs
 ```

 - Action Client 노드 실습을 위한 패키지 생성 및 `/play_motion2` 액션을 사용하기 위한

   `play_motion2_msgs` 인터페이스 종속성 추가. 

 ```bash
 import rclpy
 from rclpy.node import Node
 from rclpy.action import ActionClient
 from play_motion2_msgs.action import PlayMotion2
 import sys
 
 class PlayMotionClient(Node):
     def __init__(self):
         super().__init__('play_motion_client')
         self.action_client = ActionClient(
             self,
             PlayMotion2,
             '/play_motion2',
         )
         self.get_logger().info('Play Motion Client has been started')
 
     def send_goal(self, motion_name, skip_planning=False):
         self.get_logger().info('Waiting for action server...')
         self.action_client.wait_for_server()
 
         # PlayMotion2 액션의 goal 메시지 생성
         goal_msg = PlayMotion2.Goal()
         goal_msg.motion_name = motion_name
         goal_msg.skip_planning = skip_planning
 
         self.get_logger().info(f'Sending goal: {motion_name} (skip_planning: {skip_planning})')
 
         # 비동기로 goal 전송
         self.send_goal_future = self.action_client.send_goal_async(
             goal_msg,
             feedback_callback=self.feedback_callback
         )
         self.send_goal_future.add_done_callback(self.goal_response_callback)
 
     def goal_response_callback(self, future):
         goal_handle = future.result()
         if not goal_handle.accepted:
             self.get_logger().error('Goal rejected')
             return
 
         self.get_logger().info('Goal accepted')
         self.get_result_future = goal_handle.get_result_async()
         self.get_result_future.add_done_callback(self.get_result_callback)
 
     def get_result_callback(self, future):
         result = future.result().result
         if result.success:
             self.get_logger().info('Motion completed successfully!')
         else:
             self.get_logger().error(f'Motion failed with error: {result.error}')
 
         self.get_logger().info('Action completed')
 
     def feedback_callback(self, feedback_msg):
         feedback = feedback_msg.feedback
         # 현재 시간 출력 (초와 나노초)
         self.get_logger().info(
             f'Current time - sec: {feedback.current_time.sec}, '
             f'nanosec: {feedback.current_time.nanosec}'
         )
 
 def main(args=None):
     rclpy.init(args=args)
     action_client = PlayMotionClient()
 
     # 명령줄 인자 처리
     motion_name = 'home'  # 기본값
     skip_planning = False  # 기본값
 
     if len(sys.argv) > 1:
         motion_name = sys.argv[1]
     if len(sys.argv) > 2:
         skip_planning = sys.argv[2].lower() == 'true'
 
     try:
         action_client.send_goal(motion_name, skip_planning)
         rclpy.spin(action_client)
     except KeyboardInterrupt:
         action_client.get_logger().info('Keyboard interrupt received, shutting down...')
     finally:
         rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `from play_motion2_msgs.action import PlayMotion2`
    - tiago 로봇 모션제어를 위한 `PlayMotion2` 액션 타입 import
 - `PlayMotionClient` 클래스
    - ActionClient 객체 생성 시 인자로 첫번째 현재 노드 인스턴스로 self,

      두번째 인자로 사용할 액션 타입 PlayMotion2, 세번째 인자로 액션 서버의

      이름인 `/play_motion2`를 넣어준다.
    - `send_goal` 함수
       - ActionClient 객체인 `_action_client`에서 `wait_for_server`

         함수를 호출하여 클라이언트에서 요청을 보내려고 하는 서버가 사용가능한지 확인.
       - `PlayMotion1.Goal()`객체 생성을 통해 `goal_msg`를 생성하고

          메시지 형식에 따라 `goal_msg.motion_name`과 `goal_msg.skip_planning`

          변수에 필요한 값 대입.
       - `send_goal_async()`함수를 통해 작성한 goal 메시지 전송 및 feedback_callback

          함수를 등록하여 액션 서버 쪽에서 보내는 feedback을 받는다.

          비동기로 전송하였기 때문에, goal을 받기 위한 핸들러 역할을 하는 `send_goal_future`에

          반환값을 받는다.
       - `send_goal_future` 객체에 추가로 `goal_response_callback`이라는 콜백함수를 동록.

          `goal_response_callback` 함수는 액션을 수행했을 때의 결과가 아닌 액션 서버 쪽에서

          클라이언트가 보낸 goal 메시지의 승낙 여부를 체크하는 함수이다.
    - `goal_response_callback` 함수
       - goal 메시지가 처리될 때 트리거 발생.
       - 서버가 goal 메시지를 수락했는지 확인하고 거부되었을 경우 메시지를 인쇄
       - 목표가 수락되면 `goal_result_async`함수로 결과를 요청하고, 이 함수는

         결과가 준비되면 완료될 퓨처를 반환하고 이를 `get_result_future`에 저장.
       - `get_result_future` 객체는 액션 수행이 완료될 때 트리거될 콜백 함수도

          할당해야 한다. 이 함수를 `get_result_callback`이라고 한다.
    - `get_result_callback` 함수
       - 액션 수행 결과를 받아 성공/실패 여부를 확인하고, 결과에 따른 적절한 로그 메시지를 출력.
    - `feedback_callback` 함수
       - 액션 수행 중 서버로부터 받는 피드백 메시지를 처리할 수 있다.
       - 그러나, 액션 서버에서 feedback 을 보내주지 않으면 interface에 feedback이 정의

         되어있어도 동작하지 않는다.
 - `main` 함수
   - `PlayMotionClient` 클래스의 인스턴스를 생성하고 터미널 명령줄 인자를 통해

      goal_msg 형식에 넣을 `motion_name`이름을 받는다.
   - `send_goal` 함수를 호출하여 모션 실행을 요청
   - `rclpy.spin`으로 노드를 실행하여 콜백들이 처리 될 수 있도록 한다. 
 
 ```bash
 entry_points={
     'console_scripts': [
         'play_motion_client = tutorial_action.play_motion_client:main',
     ],
 },
 ```

 - `tutorial_action/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가

 ```bash
 colcon build --symlink-install --packages-select tutorial_action
 ```

 - 워크스페이스 루트 디렉토리에서 패키지를 다시 빌드. 

 ```bash
 ros2 run tutorial_action play_motion_client
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/9be0a78a-9f8b-4b05-b73d-773bede9f3e5" height="300" width="550">
 </div> 

 <div align="left">
     <img src="https://github.com/user-attachments/assets/d4c3eb11-676c-4edc-a6b8-afadb6720ce9" height="200" width="450">
 </div> 

 - 액션 클라이언트 노드를 실행하는 명령어에 시스템 변수 `reach_floor`를 넣어서 실행하면

   tiago_gazebo 시뮬레이션 환경에서 로봇팔이 바닥에 닿게 움직이는 액션 동작을 수행하는 것 확인 가능. 

## Ch05-04. (실습) Action Programming (2) - Server
---

 ### Action Server Node 

 - 목표
   - `turtlesim/action/RotateAbsolute` 액션 타입을 활용하여 tiago 로봇의 회전을 제어하는

      액션 서버 노드 생성.

 ```bash
 ros2 interface show turtlesim/action/RotateAbsolute
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/46277ea2-96f6-484f-aa8e-352ec44b4d49" height="200" width="450">
 </div> 
 
 - `turtlesim/action/RotateAbsolute` 타입은
    -  goal : theta( 목표 회전 각 )
    -  result : delta( 목표 회전각과 실제 회전각의 누적 차 )
    -  feedback : remaining( 액션 수행 중, 목표 회전각 까지 남은 회전각 )
  
 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 - `tiago_gazebo` 시뮬레이션 환경 실행.

 ```bash
 import rclpy
 from rclpy.action import ActionServer
 from rclpy.node import Node
 from turtlesim.action import RotateAbsolute
 from geometry_msgs.msg import Twist
 import time
 
 class RotateActionServer(Node):
     def __init__(self):
         super().__init__('rotate_action_server')
 
         # Action server 초기화
         self.action_server = ActionServer(
             self,
             RotateAbsolute,
             'rotate_tiago',
             self.execute_callback
         )
 
         # cmd_vel 퍼블리셔 설정
         self.cmd_pub = self.create_publisher(Twist, 'cmd_vel', 10)
 
         # 현재 회전 각도 변수
         self.current_angle = 0.0
 
     def execute_callback(self, goal_handle):
         self.get_logger().info('Executing goal to rotate to angle: %f' % goal_handle.request.theta)
 
         # 목표 각도와 현재 각도 차이 계산
         target_angle = goal_handle.request.theta
         angle_diff = target_angle - self.current_angle
 
         # 회전 방향 및 속도 설정
         twist_msg = Twist()
         twist_msg.angular.z = 0.5 if angle_diff > 0 else -0.5
 
         # 피드백 메시지 초기화
         feedback_msg = RotateAbsolute.Feedback()
 
         # 목표 각도에 도달할 때까지 반복
         while abs(angle_diff) > 0.01:
             self.cmd_pub.publish(twist_msg)
 
             # 각도 차이 업데이트
             angle_diff -= 0.01 * twist_msg.angular.z  # 간단한 각도 차이 갱신
 
             # 피드백 메시지 업데이트 및 publish
             feedback_msg.remaining = abs(angle_diff)
             goal_handle.publish_feedback(feedback_msg)
 
             # 각도 도달 확인
             if abs(angle_diff) <= 0.01:
                 break
 
             time.sleep(0.01)
 
         # 목표에 도달하면 정지
         twist_msg.angular.z = 0.0
         self.cmd_pub.publish(twist_msg)
 
         # 현재 각도 초기화
         self.current_angle = 0.0
 
         # 목표 도달 및 응답
         goal_handle.succeed()
         result = RotateAbsolute.Result()
         result.delta = angle_diff
 
         self.get_logger().info('Goal achieved with delta: %f' % result.delta)
         return result
 
 
 def main(args=None):
     rclpy.init(args=args)
     node = RotateActionServer()
     rclpy.spin(node)
     node.destroy_node()
     rclpy.shutdown()
 
 if __name__ == '__main__':
     main()
 ```

 - `tutorial_action/tutorial_action/rotate_server.py` 파일을 생성하고 위의 코드 작성.
 - `from turtlesim.action import RotateAbsolute`
    - tiago 로봇 제어를 위한 `RotateAbsolute` 액션 타입 import  
 - `RotateActionServer` 클래스
    - ActionServer 객체 생성 시, 첫 번째 인자로 현재 노드 인스턴스 `self`,

      두 번째 인자로 액션 타입 `RotateAbsolute`, 세 번째 인자로 액션 이름

      `rotate_tiago` , 네 번째 인자로 액션 목표(Goal)를 수신할 때 호출되고

      액션이 수행할 작업을 주요 기능으로 가진 콜백 함수이다. 
    - 실제 로봇의 회전을 하기 위한 `/cmd_vel` 토픽의 publisher도 생성.
    - `execute_callback` 함수
      - 함수의 인자 `goal_handle`로 부터 goal 목표 회전각 theta 값을

        받아오고 목표 회전각과 실제 회전각의 차이를 `angle_diff` 변수에 저장.
      - 회전 명령 publish를 위한 `Twist` 타입 메시지를 생성해 주고,

        `RotateAbsolute` 액션 타입으로 부터 feedback_msg 도 생성.
      - while 루프문 안의 제어 주기를 0.01초로 설정하고 회전 명령 publish 및
      
        로봇의 실제 회전각과 목표 회전각 사이의 차이를 업데이트 한다.

        또한 생성된 `feedback_msg`에 값을 넣어 `goal_handle`의 `publish_feedback`

        함수로 피드백 메시지를 publish 한다.
      - 동작 수행 완료 후 로봇을 정지시킨 뒤, goal_handle의 succeed 메서드를 통해 성공으로

        설정하고 result 메시지 안에 적절한 값을 채워 반환 한다.

 ```bash
  entry_points={
     'console_scripts': [
         'play_motion_client = tutorial_action.play_motion_client:main',
         'rotate_server = tutorial_action.rotate_server:main', # 추가!
     ],
 },
 ```

 - `tutorial_service/setup.py` 파일을 열고 `entry_points` 섹션에 새로운 노드를 추가


 ```bash
 colcon build --symlink-install --packages-select tutorial_action
 ```

 - 워크스페이스 루트 디렉토리에서 패키지 다시 빌드.

 ```bash
 ros2 run tutorial_action rotate_server
 ```

 - `ros2 run` 명령어로 `/rotate_tiago` 액션을 위한 서버 노드를 실행.

 ```bash
 ros2 action send_goal -f /rotate_tiago turtlesim/action/RotateAbsolute "{theta: 3.141592}"
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/561dd6aa-0ee6-48bc-bd39-26412167d5d9" height="100" width="300">
 </div> 

<div align="left">
     <img src="https://github.com/user-attachments/assets/5cb3054f-0486-4fb2-87cc-e3c2f84e89f5" height="280" width="450">
 </div> 

 - `ros2 action send_goal -f` 명령어로 tiago 로봇이 반시계 방향으로 180도 회전하고 

   및 Action Client 노드에서 feedback 메시지가 수신되는지 확인

## Ch05-05. (실습) Interface Programming - Action
---

 ### Custom Action 만들기 

 - 목표
   - 지난 실습에서 사용했던 액션 인터페이스인 `turtlesim/action/RotateAbsolute`를

     거의 그대로 활용하여 커스텀 액션 작성.
   - 기존 포맷에서 성공 여부를 나타내는 `success`만 result에 추가

 ```bash
 cd ~/ros2_ws/src/custom_interfaces
 mkdir action
 cd action
 touch RotateAbsolute.action
 ```

 - 기존에 만들었던 `custom_interfaces` 패키지에서 `action` 디렉토리 생성.
 - `RotateAbsolute.action` 파일 생성.

 ```bash
 float32 theta
 ---
 float32 delta
 bool success # 추가
 ---
 float32 remaining
 ```

 - `RotateAbsolute.action` 파일에 goal/result/feedback 섹션 정의 


 ```bash
 cmake_minimum_required(VERSION 3.8)
 project(custom_interfaces)
 
 if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   add_compile_options(-Wall -Wextra -Wpedantic)
 endif()
 
 # find dependencies
 find_package(ament_cmake REQUIRED)
 find_package(rclcpp REQUIRED)
 find_package(std_msgs REQUIRED)
 find_package(rosidl_default_generators REQUIRED)
 # uncomment the following section in order to fill in
 # further dependencies manually.
 # find_package(<dependency> REQUIRED)
 
 if(BUILD_TESTING)
   find_package(ament_lint_auto REQUIRED)
   # the following line skips the linter which checks for copyrights
   # comment the line when a copyright and license is added to all source files
   set(ament_cmake_copyright_FOUND TRUE)
   # the following line skips cpplint (only works in a git repo)
   # comment the line when this package is in a git repo and when
   # a copyright and license is added to all source files
   set(ament_cmake_cpplint_FOUND TRUE)
   ament_lint_auto_find_test_dependencies()
 endif()
 
 rosidl_generate_interfaces(${PROJECT_NAME}
   "msg/RobotStatus.msg"
   "srv/MoveRobot.srv"
   "action/RotateAbsolute.action" # 추가!
 )
 
 ament_package()
 ```

 - `custom_interfaces/CMakeLists.txt` 파일에 새로운 액션 추가

 ```bash
 colcon build --symlink-install --packages-select custom_interfaces
 ```

 - 워크스페이스 루트 디렉토리에서 패키지 빌드. 


 ```bash
 ros2 interface show custom_interfaces/action/RotateAbsolute
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/8b4e7808-643b-4213-bbd4-7c36ed671745" height="280" width="450">
 </div> 

 - `ros2 interface show` 명령어로 정의된 action 인터페이스가 생성되었는지 확인. 

 ### Custom Action을 사용한 프로그래밍
 
 ```bash
 ros2 launch tiago_gazebo tiago_gazebo.launch.py is_public_sim:=True
 ```

 - tiago_gazebo 시뮬레이션 실행. 


 ```bash
 # from turtlesim.action import RotateAbsolute 대신
 from custom_interfaces.action import RotateAbsolute
 ```

 ```bash
 # 목표 도달 및 응답
 goal_handle.succeed()
 result = RotateAbsolute.Result()
 result.delta = angle_diff
 result.success = True # 추가
 ```

 - 기존 코드의 `turtlesim/action/RotateAbsolute` 인터페이스 대신 새로 만든
   `custom_interfaces/action/RotateAbsolute` 인터페이스 타입으로 수정.
 - goal 목표 도달 시, result 핸들러에 success 성공 여부 데이터 추가 

 ```bash
 ros2 run tutorial_action rotate_server
 ```

 - 새로 정의한 액션 인터페이스 테스트를 위해 rotate_server 노드 실행. 

 ```bash
 ros2 action send_goal -f /rotate_tiago custom_interfaces/action/RotateAbsolute "{theta: 1.5708}"
 ```
 <div align="left">
     <img src="https://github.com/user-attachments/assets/27fdaa0d-d9ff-4b55-ba48-d297cc4b8483" height="80" width="270">
 </div>

 <div align="left">
     <img src="https://github.com/user-attachments/assets/9e662856-4d8e-47b5-82a3-7d36885c033d" height="250" width="450">
 </div>

 - `ros2 action send_goal` 명령어를 실행하여 새롭게 정의된 인터페이스로 액션 요청 시, tiago 로봇이 동작하는지

   확인 및 새롭게 추가된 result 섹션의 success 데이터가 goal 수행 완료 시, 출력되는지 확인. 



