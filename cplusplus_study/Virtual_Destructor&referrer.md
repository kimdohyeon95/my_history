### -  가상 소멸자(Virtual Destructor)와 참조자(referrer)의 참조 가능성 
<br>

 #### 1) 가상 소멸자 존재하지 않는 경우 
![image]()
![image]()
![image]()

 <div align="left">
  <img src="https://github.com/user-attachments/assets/3e692355-f355-4339-995a-ee3c7d3f78e3" height="450" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/10c6a9c5-c7d2-407b-b9a9-57e44dbc77bb" height="150" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/cbaccba8-8ff9-4e9a-a9cb-3e36c27ad1e9" height="25" width="250">
</div>

 #### 2) 가상 소멸자  존재하는 경우

<div align="left">
  <img src="https://github.com/user-attachments/assets/5463d1c0-5ecd-4078-bff5-055f1fadc075" height="450" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/aa675b65-4d21-4a23-9740-7e2fd0c511cc" height="180" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/8db82e0c-f866-4eb9-9094-1e89867022d4" height="50" width="250">
</div>

>> ✅ **가상 소멸자란 virtual로 선언된 소멸자를 의미한다. 위의 예제 처럼 상속 관계에 있는 클래스에서 기초클래스 First형 포인터로**
>>
>> **유도클래스의 객체를 생성할 경우 그 객체 소멸 시, 클래스 소멸자가 가상 소멸자가 아닌 경우 기초클래스 First클래스의 소멸자만 호출이**
>>
>> **된다.**

>> ✅ **이는 메모리 누수현상을 일으키고 객체의 소멸과정에서는 포인터 변수의 자료형에 상관없이 모든 소멸자가 호출되어야 한다.**
>>
>> **이를 위해서 소멸자 앞에 virtual 키워드를 추가 하면 된다.**

>> ✅ **가상 함수와 마찬가지로 기초 클래스의 소멸자만 virtual 키워드를 추가하면 유도 클래스의 소멸자들은 모두 가상 소멸자로**
>>
>> **선언이 된다.**

 #### 3) 가상 소멸자의 호출 순서 

<div align="left">
  <img src="https://github.com/user-attachments/assets/2b13ad57-3e76-45b0-8c99-ebc8ad05a2fb" height="450" width="700">
</div>

>> ✅ **가상 소멸자가 호출되면 상속 계층 구조상의 맨 아래에 존재하는 유도 클래스의 소멸자가 대신 호출되면서, 기초 클래스의 소멸자가**
>>
>> **순차적으로 호출됨.**
