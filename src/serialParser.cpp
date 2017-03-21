#include "src/serialParser.h"
std::vector<double> parseSerial(QBluetoothSocket *socket) {
  QByteArray line;
  while (socket->canReadLine()) {
    line = socket->readLine().trimmed();
  }
  QString res = QString::fromUtf8(line.constData(), line.length());
  std::vector<double> valueVector;

  QRegularExpression getDoubles("[-+]?[0-9]*\\.?[0-9]+");
  QRegularExpressionMatchIterator i = getDoubles.globalMatch(res);
  uint8_t j = 0;
  while (i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    if (match.hasMatch()) {
      valueVector.push_back(match.captured().toDouble());
      j++;
    }
  }
  return valueVector;
}
