 - ### 1. this 포인터의 이해 
 <br>
 
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/b8f7bc44-52b2-486f-ad2f-e12bf2ca9d0c" height="500" width="350">
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/8231adf3-aaa6-4961-b823-99bf195b7206" height="100" width="300">
</div>

>> ✅ **클래스의 멤버 함수내에서 객체 자기자신을 가리키는 용도로 사용되는 this 포인터가 사용될 수  있다.**

>> 위 예시에서 GetThisPointer함수의 반환형이 SoSimple 의 포인터형이고 반환값이 this 인 것을 알 수 있다.

>> 위 프로그램의 결과를 보면 sim1/sim2 객체가 생성될 때 생성자 안에서 객체 주소를 출력 한 값과 ptr1/ptr2가
>>
>> GetThisPointer함수를 통해서 반환받은 객체 포인터 출력값이 같은 것을 알 수 있다.

<br>

- ### 2. this 포인터의 활용
<br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/2954953a-3d5b-4d19-85c4-b6d255b683c0" height="350" width="300">
</div>

>> 위의 예제에서 TwoNumber 클래스의 생성자의 매개변수 num1과 num2는 멤버변수 num1/num2 가 서로 일치한다.
>>
>> 이러한 경우 this 포인터를 이용하여 구분할 수 있는데 this 포인터를 사용하게 되면 객체를 참조하는 포인터이기 때문에
>>
>> 객체의 포인터를 가지고는 지역변수에 접근이 불가능하기 때문에 멤버변수 num을 의미한다고 볼 수 있다. 
