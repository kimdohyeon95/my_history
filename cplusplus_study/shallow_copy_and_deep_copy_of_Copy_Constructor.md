 - ### 1. Copy Constructor(복사 생성자)의 얕은복사 깊은복사
<br>

  #### 1) 얕은 복사 (Shallow copy)

<p align="left">  
  <img src="https://github.com/user-attachments/assets/53a79dae-4131-4469-ad0a-fb1134394c34" width="40%"height="400">  
  <img src="https://github.com/user-attachments/assets/fd8f75b7-769c-47f7-8261-bf4dff9dba2c" width="50%" height="250">
</p>

<div align="left">
  <img src="https://github.com/user-attachments/assets/25b61ce4-b75a-4922-9a64-a1a76bd7dc70" height="100" width="300">
</div>

>> ✅ 복사 생성자의 문제는 클래스의 멤버변수가 힙 메모리 공간을 참조할 때 나타난다.

>> 위 예제에서 Person man2=man1; 문장을 통해 디폴트 복사생성자가 호출되고 멤버 대 멤버 복사 즉 얕은 복사가 이뤄지기 
>>
>> 때문에 man1 객체의 멤버 변수 name 문자열을 man1과 man2 두객체가 동시에 참조하는 현상이 발생한다. 

>> ✅ **따라서 객체가 소멸될 때, man1 혹은 man2 객체중에 어느 하나가 먼저 소멸되면서 남은 하나는 delete []name**
>>
>> **문장을 실행할 때 이미 name 멤버변수는 소멸된 상태이기 때문에 문제가 발생한다.**

  #### 2) 깊은 복사 (Deep copy)


<p align="left">  
  <img src="https://github.com/user-attachments/assets/2979c169-edec-4bc3-b221-d00eaf807f49" width="40%"height="400">  
  <img src="https://github.com/user-attachments/assets/a76c9cf4-610a-4eb8-99ee-fa481b08a76b" width="50%" height="250">
</p>

<div align="left">
  <img src="https://github.com/user-attachments/assets/10bb5c72-0b36-4cb2-9ac3-33b13f441f12" height="100" width="300">
</div>

>> ✅ 위 예제에서는 Person 클래스의 복사 생성자를 별도로 정의하여 man2 객체를 생성 시, 멤버변수 name에 대해
>>
>> **new 연산자를 이용한 동적할당을 통해 man1의 멤버변수 name과 별도의 메모리 공간을 할당하여 man1의 문자열을 가르키기**
>>
>> **때문에 깊은 복사가 발생하여** 객체 소멸시 소멸자가 man1/man2에 대한 name 멤버변수에 대해 동적할당을 정상적으로
>>
>> 해제 하는것을 알 수 있다. 






