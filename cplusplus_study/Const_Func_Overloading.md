- ### 1. const 함수 Overloading
  <br>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/2c043889-a17a-4629-8dec-77b4e508a41d" height="400" width="350">
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/e3d3553a-a2bd-4bb0-a8c4-0f80af8daf28" height="200" width="350">
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/120d4980-fdb4-4bf4-bf76-71a1069b4e6e" height="100" width="300">
</div>

>> ✅ **함수의 오버로딩에는 매개변수의 개수나 자료형이 다른 것 뿐만 아니라 const의 선언 유무로도**
>>
>> **오버로딩의 조건이 될 수 있다.** 

>> 위의 예제에서 SoSimple obj1(2);과 const SoSimple obj2(7); 문장에서 처럼 일반 객체와 const 객체를 선언하고
>>
>> obj1 객체는 일반 객체이므로 obj1.SimpleFunc(); 함수를 호출 할 때는 const선언이 되어있지 않은 SoSimple함수가
>>
>> 호출되고 obj2 객체는 const 객체이므로 const 선언이 되어있는 SoSimple함수가 호출된다.
>>
>> 마지막으로 YourFunc(obj1); 과 YourFunc(obj2);는 모두 YourFunc 함수의 매개변수가 const 참조자로 받기 때문에
>>
>> obj.SimpleFunc 함수 호출 결과로 const 멤버함수가 호출된다. 
