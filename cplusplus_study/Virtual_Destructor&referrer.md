### - 1. 가상 소멸자(Virtual Destructor)와 참조자(referrer)의 참조 가능성 
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

<br>

### - 2. 참조자의 참조 가능성 
<br>

<div align="left">
  <img src="https://github.com/user-attachments/assets/43d78c6c-9bca-4e71-9cac-874ed3b3c059" height="450" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/917e05d8-27d5-4e65-b732-0764d9a02dd3" height="450" width="350">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/83154006-acaa-4f23-b8cf-9f2bcaca8e58" height="150" width="250">
</div>

>> ✅ **C++에서는 AAA형 포인터 변수 뿐만 아니라 참조자에 대해서도 AAA 객체 또는 AAA를 직적 혹은 간접적으로 상속하는 모든 객체를**
>>
>> **참조할 수 있다.**

>> ✅ **클래스의 멤버함수를 호출 할 때에서 포인터 변수의 자료형에 따라서 호출할 수 있는 함수가 정해지듯이 참조자를 통한 함수 호출을**
>>
>> **진행할 때에도 동일하게 적용된다.**

>> 위 예제의 Second &sref = obj; 문장처럼 Second 클래스를 상속하는 Third 클래스의 객체인 obj는 Second형 참조자로 참조가
>>
>> 가능함을 알 수 있고, 참조자가 Second형 이기 때문에 FirstFunc() 함수와 SecondFunc()함수가 호출 가능하다.
>>
>> 또한 sref.SimpleFunc(); 문장은 SimpleFunc() 함수가 가상함수이므로 sref 참조자에 참조된 Third 클래스의 객체에 정의된
>>
>> SimpleFunc 함수가 호출된다. 

