### LDR Dividers (x4)
Each LDR forms a divider with 10 kΩ to GND.
- LDR → +5 V
- Junction (LDR–10k) → Arduino A0..A3
- 10 kΩ → GND

### Servos
- Servo +5 V → external 5 V supply
- Servo GND → external GND
- Servo signal → D9 (azimuth), D10 (elevation)
- **Common ground** between external 5 V and Arduino GND

### Power Path
Solar panel → charge/BMS → 18650 pack → boost to 5 V USB
(Optional: separate buck 5 V rail for servos)
