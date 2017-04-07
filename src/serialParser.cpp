#include "src/serialParser.h"

void parseSerial(QBluetoothSocket* socket, std::vector<dataStream>& vec) {
  QByteArray line;
  while (socket->canReadLine()) {
    line = socket->readLine().trimmed();
  }
  QString                         res = QString::fromUtf8(line.constData(), line.length());
  QRegularExpression              getDoubles("[-+]?[0-9]*\\.?[0-9]+");
  QRegularExpressionMatchIterator i = getDoubles.globalMatch(res);
  uint8_t                         j = 0;
  while (i.hasNext()) {
    QRegularExpressionMatch match = i.next();
    if (match.hasMatch()) {
      vec[j].value = match.captured().toDouble() * vec[j].multiplier;
      j++;
    }
  }
}
