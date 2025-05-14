- ### 1. Constructor( 생성자 )
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
                    
                    
                    
                    
                    
                    
                              
