# เพิ่มเติมมี 2 ข้อ
1. เพิ่ม Save MessageBox เมื่อกดปุ่ม ❌ โดยใช้ QCloseEvent  กรณีเปิดโปรแกรมใหม่แล้วเขียนใน Line edit ก็จะถามว่า Save ไหม หรือถ้าเปิดไฟล์(File) แล้วมีการแก้ไขก็จะขึ้นโชว์ </br>
    * กรณี  เปิดโปรแกรมใหม่แล้วเขียนใน Line edit
    ![image](https://user-images.githubusercontent.com/81642936/155089405-6468dc67-c833-42d5-9b3b-297361fc1421.png)
    * กรณี เปิดไฟล์แล้วแก้ไข
    ![image](https://user-images.githubusercontent.com/81642936/155089822-ff8b9023-d7f7-437b-8c6b-5ed6fc12da63.png)
    ![image](https://user-images.githubusercontent.com/81642936/155089961-d21f5b4b-65dc-46c3-a45d-5af1dff1ed81.png)    
2. ใน Save MessageBox จะมีคำว่า "Do you want to changes to +ชื่อไฟล์"ด้วยนะ
# สิ่งที่ต้องเพิ่ม
* New File 🔥
  * กรณีที่ เปิดโปรแกรม ขึ้นมาแล้วไม่ทำอะไรก็จะไม่ทำอะไร(แต่จริงๆต้อง clear เพื่อให้แน่ใจ)
  * กรณีที่ เปิดไฟล์(File) ขึ้นมาแล้วไม่ทำอะไรก็จะไม่ทำอะไร แต่ถ้ามีการแก้ไขก็จะขึ้น Save MessageBox ก่อนจากนั้นค่อย clear
