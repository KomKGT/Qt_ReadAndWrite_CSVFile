# เพิ่ม Code กรณีมีค่าติดลบเข้ามาให้กราฟขยายได้ไปจนถึงช่วงลบและช่วงบวก
เดิม</br>
```C++
        double max_x = *max_element(v_x.begin(), v_x.end());
        double max_y = *max_element(v_y.begin(), v_y.end());
        ui->plot->xAxis->setRange(0,max_x); //max_x คือค่ามากสุดที่แกน x จะโชว์ได้
        ui->plot->yAxis->setRange(0,max_y); //max_y คือค่ามากสุดที่แกน y จะโชว์ได้
```
