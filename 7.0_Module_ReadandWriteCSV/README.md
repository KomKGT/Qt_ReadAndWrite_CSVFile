# เพิ่มเติมมี 2 ข้อ
1. เพิ่ม Save MessageBox เมื่อกดปุ่ม ❌ โดยใช้ QCloseEvent ในกรณีที่แก้ไขใน Line edit หรือ เปิดโปรแกรมใหม่แล้วเขียนใน Line edit ก็จะถามว่า Save ไหม
  ![image](https://user-images.githubusercontent.com/81642936/155089405-6468dc67-c833-42d5-9b3b-297361fc1421.png)
2. ใน Save MessageBox จะมีคำว่า "Do you want to changes to +ชื่อไฟล์"ด้วยนะ
# สิ่งที่ต้องเพิ่ม
* New File 🔥
  * กรณีที่ เปิดโปรแกรม ขึ้นมาแล้วไม่ทำอะไรก็จะไม่ทำอะไร(แต่จริงๆต้อง clear เพื่อให้แน่ใจ)
  * กรณีที่ เปิดไฟล์(File) ขึ้นมาแล้วไม่ทำอะไรก็จะไม่ทำอะไร แต่ถ้ามีการแก้ไขก็จะขึ้น Save MessageBox ก่อนจากนั้นค่อย clear
