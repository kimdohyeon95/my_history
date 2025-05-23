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

