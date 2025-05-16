- ### Copy Constructor (복사 생성자)
<br>

  #### 1) 복사 생성자의 이해 
<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/0c6ffb88-1cd6-4b00-8e09-1ff084d4286b" height="450" width="450">
</div>

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/96de1809-4c54-4439-8b3a-425f58809e02" height="100" width="400">
</div>

>> ✅ **main문에서 SoSimple sim2=sim1; 문장은 SoSimple sim2(sim1); 문장으로 치환이 되고 이는 다음의 뜻을 가진다.**

>> ✅ **SoSimple 형 객체를 생성하고 객체의 이름은 sim2 이며 객체 sim1을 인자로 받을 수 있는 생성자 호출을 통해**
>>
>> **객체생성을 완료한다.**

>> SoSimple클래스에서 SoSimple(SoSimple &copy) 로 정의된 생성자를 가리켜 복사 생성자 라고 한다.

>> 복사 생성자는 정의 형태가 특이해서 붙은 이름이 아니라 호출시점이 일반 생성자에 비해 특이해서 생긴 것이다.

>> 원래 복사 생성자의 정의를 별도로 하지 않아도 SoSimple sim2(sim1);과 같은 문장이 실행되고 멤버 대 멤버
>>
>> 복사가 이루어 지는 것을 알 수 있다. 별도의 복사 생성자를 정의하지 않아도 디폴트 복사 생성자가 정의되어 있기 때문이다.

   #### 2) explicit 키워드를 이용한 묵시적 형변환 제한 

<div align="left">
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="https://github.com/user-attachments/assets/63a20a12-1cfd-4f50-8cb0-14c3836c4563" height="200" width="450">
</div>

>> ✅ 위 예제처럼 복사 생성자 정의 앞에 explicit 키워드를 사용하면 oSimple sim2=sim1; 문장이 SoSimple sim2(sim1);로
>>
>> 묵시적 형변환이 되는 것을 막을 수 있다. 
