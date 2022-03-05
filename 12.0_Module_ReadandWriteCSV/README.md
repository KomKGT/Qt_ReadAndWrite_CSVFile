# เพิ่ม Code กรณีมีค่าติดลบเข้ามาให้กราฟขยายได้ไปจนถึงช่วงลบและช่วงบวก
เดิม (BEFORE) </br>
```C++
        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());
        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(0,max_y); //max_y คือค่ามากสุดที่แกน y จะโชว์ได้
```
จากรูปนี่เราได้ทำการ Plot กราฟพาราโบลาคว่ำแต่กราฟไม่สามารถแสดงผลออกมาได้เนื่องจาก Code เดิมไม่รองรับ
![image](https://user-images.githubusercontent.com/81642936/156870450-e4c39091-2be4-43cb-9c6c-df937454b86c.png)
ใหม่ (AFTER) </br>
```C++
        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());
        double min_y = *min_element(v_y.begin(), v_y.end());
        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(min_y,max_y); //min_y คือค่าน้อยสุดที่จะโชว์ได้ ,max_y คือค่ามากสุดที่แกน y จะโชว์ได้
```
