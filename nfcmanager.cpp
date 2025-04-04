
#include "nfcmanager.h"
#include <QDebug>



// Déclarez les technologies de découverte NFC
static const uint8_t DiscoveryTechnologies[] = {TECH_PASSIVE_NFCA, TECH_PASSIVE_NFCB, TECH_ACTIVE_NFCA};

NfcManager::NfcManager(QObject *parent) : QThread(parent)
{
    if (NxpNci_Connect() == NFC_ERROR) {
        qDebug() << "Erreur : Impossible de se connecter au périphérique NFC";
        return;
    }

    if (NxpNci_ConfigureSettings() == NFC_ERROR) {
        qDebug() << "Erreur : Impossible de configurer les paramètres NFC";
        return;
    }

    if (NxpNci_ConfigureMode(NXPNCI_MODE_RW) == NFC_ERROR) {
        qDebug() << "Erreur : Impossible de configurer le mode NFC";
        return;
    }

}

NfcManager::~NfcManager()
{

    stopDiscovery();  // Arrêter la découverte NFC proprement
    NxpNci_Disconnect();  // Fermer la connexion NFC

}



void NfcManager::run()
{
    stop = false;
    qDebug() << "Thread is running ....";

    do
    {
        qDebug() << "do ...while....";
        getCardID();
        if(stop) qDebug() << "Stop dans run() ";
    }while(!stop);

    qDebug() << "Thread will stop ....";


}

bool NfcManager::startDiscovery()
{

    // Créer un tableau mutable à partir du tableau constant
    unsigned char mutableTechnologies[] = {
        TECH_PASSIVE_NFCA,
        TECH_PASSIVE_NFCB,
        TECH_ACTIVE_NFCA,
        TECH_ACTIVE_NFCF
    };

    return (NxpNci_StartDiscovery(mutableTechnologies, sizeof(mutableTechnologies)) == NFC_SUCCESS);
}

void NfcManager::stopDiscovery()
{
    NxpNci_StopDiscovery();
}

void NfcManager::getCardID()
{
    qDebug() << "appel getCardID";


    if (NxpNci_WaitForDiscoveryNotification(&RfIntf)  != NFC_SUCCESS) {
        qDebug() << "Aucune carte détectée";

    }


    else if (RfIntf.ModeTech == (MODE_POLL | TECH_PASSIVE_NFCA)) {
        cardID.assign(RfIntf.Info.NFC_APP.NfcId,
                      RfIntf.Info.NFC_APP.NfcId + RfIntf.Info.NFC_APP.NfcIdLen);
        emit cardDetected(cardID);

    }
    qDebug() << "getCardID sleep 500";
    msleep(500);
}

void NfcManager::stopRun()
{
    NxpNci_Disconnect();
    stop = true;

}
