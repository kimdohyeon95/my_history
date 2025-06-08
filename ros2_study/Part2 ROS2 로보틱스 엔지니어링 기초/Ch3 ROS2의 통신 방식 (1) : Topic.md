## Ch03-01. Topic & Interface 개요 
---

 ### Interface란?

<div align="left">
  <img src="https://github.com/user-attachments/assets/91247096-f925-447c-94b9-aa02b70693ae" height="350" width="700">
</div>

 ### Topic 이란?
 
<div align="left">
  <img src="https://github.com/user-attachments/assets/9c09f0db-43f1-4ec3-939b-dde7a32c41e2" height="350" width="700">
</div>

 - 비동기 통신
  => subscriber 가 publisher 특정 노드를 등록해야하는 과정이 없고, topic 에 해당되는 이름만 맞춰 주면

     publisher 로 부터 데이터를 받을 수 있다.

 - 다대다 통신
  => 하나의 publisher 가 여러 개의 subscriber에게 메세지를 보낼 수 있고, 하나의 topic 에 여러개의 

     publisher 가 동일한 메세지를 발행 할 수 도 있다.

 - 고유한 메시지 타입
  => publisher와 subscriber가 모두 동일한 데이터 구조를 사용할 수 있도록 정의해야 한다. 

 - 보통 topic 은 연속적으로 혹은 특정 주기로 데이터를 보낼 때 사용.
 - 
 ### Interface Type 정의: Message

<div align="left">
  <img src="https://github.com/user-attachments/assets/e7b69749-28ee-4016-ad23-8fe9ab496318" height="350" width="700">
</div>

