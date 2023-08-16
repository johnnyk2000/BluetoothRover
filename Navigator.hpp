#pragma once

/*
1-2 left
3-4 right
*/

class Navigator {
private:
  const int m_torque = 100;
  bool m_initialized;
  int m_enA, m_in1, m_in2, m_in3, m_in4, m_enB;

public:
  Navigator();

  // ~Navigator(); // use default

  void begin(int enA, int in1, int in2, int in3, int in4, int enB);

  void stop();

  void forward();

  void backup();

  void right();

  void left();

};

Navigator::Navigator() : m_initialized(false) {
  //
}

void Navigator::begin(int enA, int in1, int in2, int in3, int in4, int enB) {
  m_enA = enA;
  m_in1 = in1;
  m_in2 = in2;
  m_in3 = in3;
  m_in4 = in4;
  m_enB = enB;

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void Navigator::stop() {
  digitalWrite(m_in1, LOW);
  digitalWrite(m_in2, LOW);
  digitalWrite(m_in3, LOW);
  digitalWrite(m_in4, LOW);
  digitalWrite(m_enA, 0);
  digitalWrite(m_enB, 0);
}

void Navigator::forward() {
  digitalWrite(m_in1, HIGH);
  digitalWrite(m_in2, LOW);
  digitalWrite(m_in3, HIGH);
  digitalWrite(m_in4, LOW);
  digitalWrite(m_enA, m_torque);
  digitalWrite(m_enB, m_torque);
}

void Navigator::backup() {
  digitalWrite(m_in1, LOW);
  digitalWrite(m_in2, HIGH);
  digitalWrite(m_in3, LOW);
  digitalWrite(m_in4, HIGH);
  digitalWrite(m_enA, m_torque);
  digitalWrite(m_enB, m_torque);
}

void Navigator::left() {
  digitalWrite(m_in1, HIGH);
  digitalWrite(m_in2, LOW);
  digitalWrite(m_in3, LOW);
  digitalWrite(m_in4, HIGH);
  digitalWrite(m_enA, m_torque);
  digitalWrite(m_enB, m_torque);
}

void Navigator::right() {
  digitalWrite(m_in1, LOW);
  digitalWrite(m_in2, HIGH);
  digitalWrite(m_in3, HIGH);
  digitalWrite(m_in4, LOW);
  digitalWrite(m_enA, m_torque);
  digitalWrite(m_enB, m_torque);
}