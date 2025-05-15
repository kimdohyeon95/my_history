- ### 1. Constructor(생성자)
 <br>
 
  #### 1) 생성자의 정의

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/f7fc7973-447c-48ac-9d7a-96ebec234126" height="380" width="650">
</div>

>> ✅ **생성자란 클래스의 객체 생성 시 딱 한번 호출되어 호출과 동시에 멤버변수를 초기화 하는 목적으로 사용된다.**

>> ✅ **생성자의 특징은 클래스의 이름과 함수의 이름이 동일하고 반환형이 선언되어있지 않다.**

>> ✅ **생성자도 함수의 일종이기 때문에 오버로딩이 가능하고 매개변수에 디폴트 값을 설정할 수 있다.**


   #### 2) 생성자의 호출 시 유의사항 

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/f975da14-7841-4e1f-a5a4-595849b1e0c9" height="470" width="350">
</div>

>> ✅ **클래스 객체를 생성하는 경우 위 예제처럼 디폴트 생성자나 매개변수가 없는 생성자를 호출할 때 SimpleClass sc1();**
>>
>>    **문장이 잘못된 이유는 클래스 외부 함수 원형의 지역적 선언과 관련이 있다.**
>>
>>    **외부 함수의 원형을 지역적으로 선언할 수도 있기 때문에 컴파일러 입장에서 SimpleClass sc1(); 문장을 void형 생성자**
>>
>>    **호출문으로 인정해 버릴 경우 컴파일러는 객체생성문인지 함수의 원형선언인지를 구분할 수 없기 때문이다.** 
                    

   #### 3) Member Initializer (멤버 이니셜라이저)를 이용한 멤버 초기화

<p align="left">  
  <img src="https://github.com/user-attachments/assets/475feb00-0f0d-4454-9fb2-0e71e22c146c" width="40%" height="200">  
  <img src="https://github.com/user-attachments/assets/b4670436-4f8a-42b1-90f2-f041f0a25676" width="40%" height="200">
</p>


<p align="left">  
  <img src="https://github.com/user-attachments/assets/b9e2bb78-0965-4b5a-bc87-963a2b993990" width="40%"height="180">  
  <img src="https://github.com/user-attachments/assets/5e9265b6-b6f0-4e95-a310-0ed35dd761ac" width="50%" height="180">
</p>


>> 위의 예제는 Rectangle 클래스의 멤버 변수 중 객체 멤버 변수인 upLeft, lowRight를 Rectangle 클래스 객체 생성함과 동시에
>>
>> 초기화 하는 방법을 나타낸 것이다. Rectangle 클래스의 생성자의 `:upLeft(x1,y1), lowRight(x2, y2)` 부분이 
>>
>> 멤버 이니셜라이저를 뜻하는 것이고 이것의 의미는 `upLeft/lowRight 객체 생성과정에서 각각 x1과 y1 x2와 y2를 인자로` 
>>
>> `전달받는 생성자를 호출` 하라는 뜻이다.
>>
>> ✅ **멤버 이니셜라이저를 이용하여 객체 멤버를 초기화 할 수 있을 뿐만 아니라 선언과 동시에 초기화가 필요한 const 상수**
>>
>> **혹은 참조자에도 이용할 수 있다.**


   #### 4) Default Constructor ( 디폴트 생성자 )

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/eeb42e42-3384-4e61-b847-0d2d5c6e449d" height="250" width="600">
</div>

>> ✅ **디폴트 생성자란 `객체 생성시 반드시 하나의 생성자가 호출 되어야 한다`는 기준에 예외를 두지 않기 위해**
>>
>> **생성자를 별도로 정의하지 않은 경우에 컴파일러에 의해 자동으로 생성되는 생성자를 의미한다.**
<br>


- ### 2. Destructor (소멸자)
  
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/cd4c04c1-ce1f-4eb8-a221-4cf37d46de58" height="450" width="300">
</div>

>> ✅ **소멸자란 생성자와 마찬가지로 프로그램이 끝나면서 객체가 소멸될 때 반드시 호출되며**
>>
>> **new 키워드로 할당된 리소스의 소멸에 활용된다.**
>>
>> ✅ **반환형과 매개변수 모두 void 형으로 선언되어야 하기 때문에 오버로딩과 디폴트 매개변수를 사용할 수 없다.**
>>
>> 위 예제에서는 Person 클래스 객체 생성 시 new 키워드로 동적 할당된 멤버변수 name에 대하여 소멸자 ~Person() 에서
>>
>> delete 키워드를 통해 동적할당을 해제 시키는 것을 볼 수 있다.
