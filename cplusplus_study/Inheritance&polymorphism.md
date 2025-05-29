- ### 1. 객체 포인터의 참조 관계
<br>

  #### 1) 객체 포인터 변수

<p align="left">  
  <img src="https://github.com/user-attachments/assets/6925b5fd-be64-4f63-9726-b3aac0f5cbdd" width="40%"height="480">  
  <img src="https://github.com/user-attachments/assets/d2c4915e-dd45-49ab-abee-092308c74ffd" width="55%" height="480">
</p>

<div align="left">
  <img src="https://github.com/user-attachments/assets/18eb05f7-93f6-41a0-8e02-df437ba937d9" height="80" width="350">
</div>

>> ✅ 위 예제 main 문에서 Person *ptr1 = new Student(); 혹은 Person *ptr2 = new PartTimeStudent();
>>
>> 문장처럼 Person *ptr1 포인터 변수는 Person 객체 혹은 Person 클래스를 직접 혹은 간접적으로 상속하는 모든 객체를
>>
>> 가리킬 수 있다.

>> ✅ **IS-A 관계에의해 Student는 Person의 일종이다. PartTimeStudent 은 Student의 일종이다.**
>>
>> **따라서, PartTimeStudent은 Person의 일종이다. 라는 결론이 내려지고 Person 클래스 객체 포인터 변수로**
>>
>> **유도 클래스 Student 와 PartTimeStudent 클래스를 가리킬 수 있는 것이다.**

 #### 2) 함수 오버라이딩 

<p align="left">  
  <img src="https://github.com/user-attachments/assets/60030c76-db11-4032-8387-565c5987cf0b" width="40%"height="480">  
  <img src="https://github.com/user-attachments/assets/bafd57e8-62e1-43e3-8277-f89a1e9b48ca" width="55%" height="480">
</p>

>> PermanentWorker 클래스에는  GetPay 와 ShowSalaryInfo 멤버함수를 가지고 있다. 그런데 유도 클래스인 
>>
>> SalesWorker 클래스에도 동일한 이름과 형태로 두 함수가 정의 되어있다.

>> ✅ **이를 가리켜 함수 오버라이딩( function overriding ) 이라 한다. 이렇게 함수 오버라이딩이 되면**
>>
>> **오버라이딩된 기초 클래스의 함수는, 오버라이딩을 한 유도 클래스의 함수에 가려진다. 그래서 위의 SalesWorker**
>>
>> **클래스 내에서 GetPay 함수를 호출하면 SalesWorker 클래스에 정의된 GetPay 함수가 호출된다.**

>> 여기서, 클래스의 이름을 명시하여 기초 클래스의 오버라이딩 된 함수를 호출할 수 있다. 
>>
>> SalesWorker 클래스의 GetPay 함수에 **`PermanentWorker::GetPay()`** 의 문장은
>>
>> 오버라이딩 된기초 클래스의 GetPay 함수를 호출한다.

<br>

- ### 2. 가상 함수 ( Virtual Function )
<br>

  #### 1) 기초 클래스의 포인터 객체 참조
  
<div align="left">
  <img src="https://github.com/user-attachments/assets/d334cb28-6fa2-4ded-ad58-9ec808dc9e39" height="400" width="800">
</div>

>> ✅ **C++ 컴파일러는 포인터 연산의 가능성 여부를 판단할 때, 실제 가리키는 객체의 자료형을 기준으로 판단하지 않고,**
>>
>> **포인터의 자료형을 기준으로 판단한다.**

>> 위의 첫번째 예제에서 Derived 클래스는 Base 클래스의 유도 클래스이므로 Base 클래스의 포인터 변수에는 Derived 클래스의
>>
>> 포인터형을 가리킬 수 있고, 반대로, Derived 클래스의 포인터 변수는 Base 클래스의 포인터 변수를 가리 킬 수 없다.
>>
>> 왜냐하면, Base형의 포인터는 Derived 객체 또는 Base 객체 둘 다 가리킬 수 있기 때문이다.

<div align="left">
  <img src="https://github.com/user-attachments/assets/24e177f8-d264-446f-95e5-ab1e93164c34" height="300" width="500">
</div>

>> 두번째 예제에서, Third형 포인터 변수 tptr이 가리키는 객체는 무조건 Second형 포인터 변수 sptr도 가리킬 수 있고,
>> 
>> First형 포인터 변수 fptr도 가리킬 수 있다.

>> ✅ **예를 들어 sptr 포인터 변수는 First 클래스로 부터 상속한 Second 클래스의 포인터 형이므로** 
>>
>> **First 클래스와 Second 클래스의 public형 멤버함수에 접근이 가능하다.**
>>
>> 따라서 sptr->FirstFunc(); 문장과 sptr->SecondFunc(); 문장이 실행 될 수 있다.

  #### 2) 함수의 오버라이딩과 포인터 형 
  
<div align="left">
  <img src="https://github.com/user-attachments/assets/c7f6b83d-00d8-47e9-a3b1-a3d331402d5f" height="350" width="300">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/eff7331e-da21-4987-a500-5863ddbbe83a" height="250" width="300">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/70fc40be-d4f3-4398-976e-58763de92091" height="80" width="280">
</div>

>> 위의 First, Second, Third 클래스는 모두 상속의 관계를 가지고 있다. 

>> ✅ **sptr->MyFunc(); 문장은 Second형 포인터 변수 sptr은 Second형 포인터이니 이 변수가 가리키는 객체에는**
>> 
>> **First의 MyFunc 함수와 Second의 MyFunc 함수가 오버라이딩 관계로 존재하고 이때 오버라이딩된 Second의** 
>>
>> **MyFunc 함수가 호출된다.**

  #### 3) 가상 함수의 사용
  
<div align="left">
  <img src="https://github.com/user-attachments/assets/22f1a142-d0b4-4851-b5c2-254e8771a3b5" height="350" width="300">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/82c3f7e9-3552-42c5-9464-29e427ee7252" height="250" width="300">
</div>

<div align="left">
  <img src="https://github.com/user-attachments/assets/628ff254-6bc7-480a-a633-829d257c7f5c" height="80" width="280">
</div>

>> ✅ **함수 오버라이딩은 해당 객체에서 호출되어야 하는 함수를 바꾼다는 의미이다. 하지만 `포인터 변수의 자료형에 따라`**
>>
>> **호출되는 함수의 종류가 달라지는 것은 문제가 있다.**

>> ✅ **이러한 상황을 해결하기 위해서 가상함수가 사용된다. 가상함수는 위의 예제처럼 virtual 키워드를 통해 함수 선언 시**
>>
>> **함수의 이름 앞에 virtual 키워드를 붙여 선언한다.**

>> ✅ **이렇게 가상함수를 선언하여 오버라이딩을 하게되면 위 예제의 실행결과와 같이 함수 호출 시, `포인터의 자료형을 기반으로`**
>>
>> **`함수 호출을 하지 않고 포인터 변수가 실제로 가리키는 객체를 참조하여` 호출의 대상을 결정한다.**


