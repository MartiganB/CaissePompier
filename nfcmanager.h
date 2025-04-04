#ifndef NFCMANAGER_H
#define NFCMANAGER_H

#include <QObject>
#include <QThread>
#include <vector>
#include <cstdint>
#include <QMutex>

extern "C" {
#include "Nfc.h"  // Inclure les bibliothèques nécessaires
}


class NfcManager :  public QThread
{
    Q_OBJECT

public:
    explicit NfcManager(QObject *parent = nullptr);
    ~NfcManager();
    void run() override;
    bool startDiscovery();
    void stopDiscovery();
    void getCardID(); // Récupère l'ID de la carte RFID
    void stopRun();

signals:
    void cardDetected(std::vector<uint8_t> cardID);

private:

    void processReaderMode(NxpNci_RfIntf_t RfIntf);
    bool stop = false;
    std::vector<uint8_t> cardID;
    NxpNci_RfIntf_t RfIntf;
};

#endif // NFCMANAGER_H
