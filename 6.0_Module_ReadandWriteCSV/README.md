# ได้ทำการแก้ไขสิ่งที่ยังไม่ได้แก้ในเวอร์ชันก่อนหน้าไปแล้วมี 3 ข้อคือ
1. แก้ไขเมื่อ save แล้วจาก untitled จะเปลี่ยนเป็น ชื่อที่ทำการ save 🔥
2. แก้ไขเมื่อ save แล้วแก้ค่าใน Line edit จะขึ้น [*] 🔥
3. เว้นบรรทัดในการ save .LTN File 🔥
* เริ่มต้น (Initial) Status Bar จะขึ้น untitled.LTN
![image](https://user-images.githubusercontent.com/81642936/154917803-181da15f-80d1-4d0f-b4f8-df95ae8532ee.png)
* กรณี Save File .LTN แล้ว Status Bar จะเปลี่ยนเป็นชื่อที่เรา save
![image](https://user-images.githubusercontent.com/81642936/154918033-a6cede73-350a-4014-85b0-81ec533b8ff3.png)
![image](https://user-images.githubusercontent.com/81642936/154918158-48e4b655-933a-4f28-8856-2b1baf12f58a.png)
![image](https://user-images.githubusercontent.com/81642936/154918218-d2719b6c-105b-4a95-a110-d3a3388e9653.png)
* กรณี Save File .LTN แล้วแก้ค่าใน Line edit จะขึ้น [*] ทันที
![image](https://user-images.githubusercontent.com/81642936/154918282-7a2b1f59-5c9d-4da2-b717-12817b6eaa5c.png)
* การเปิด .LTN ไฟล์ ขึ้นมาจะต้องถูกเขียนด้วยโปรแกรมนี้เท่านั้นห้ามเขียนด้วย Notepad ได้ทำการจำลอง Save ค่าเพื่อวาดกราฟใน c++
![image](https://user-images.githubusercontent.com/81642936/154918882-b1e494c8-082f-48e1-81c6-79d85cae3f4a.png)
![image](https://user-images.githubusercontent.com/81642936/154919059-1c2d459d-ab53-45ba-a6ff-7c04775d2bc1.png)
![image](https://user-images.githubusercontent.com/81642936/154919135-e014a945-b59f-4b0d-9afe-795d3b5633fd.png)</br>
* 🔥โดยภายในไฟล์มีการวางข้อมูลแบบนี้(ใหม่)🔥</br>
![image](https://user-images.githubusercontent.com/81642936/154978597-877edeec-60cc-4e72-bcf4-5f4090338976.png)
# สิ่งที่ต้องทำต่อคือ
1. New File 
2. Export to .CSV เพื่อเปิดใน Excel
3. ประกอบกับโปรแกรมใหญ่เพื่อทดสอบ</br>
  * รับค่าจาก MODBUS RTU/TCP นำมาวาดกราฟ</br>
  * Save File 💾
      * .LTN File
      * .CSV File</br>
  * Open File 📁
      * .LTN File</br>
      * .CSV File</br>
  * New File 📝</br>
  * Printer 🖨️
