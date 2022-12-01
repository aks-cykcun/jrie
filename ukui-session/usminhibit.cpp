#include "usminhibit.h"
#include "QDBusConnection"
#include <QRandomGenerator> 
#include <limits.h>
#include <QDebug>

inhibit::inhibit(QString app_id, quint32 toplevel_xid, QString reason, quint32 flags ,quint32 cookie ,QString inhibitorName){
    this->app_id = app_id;
    this->toplevel_xid = toplevel_xid;
    this->reason = reason;
    this->flags = flags;
    this->cookie = cookie;
    this->inhibitorName = inhibitorName;
}

inhibit::~inhibit(){}


uint usminhibit::get_next_inhibitor_serial()
{
    uint serial;

    serial = inhibitor_serial++;

    if ((int32_t)inhibitor_serial < 0) {
        inhibitor_serial = 1;
    }

    return serial;
}

usminhibit::usminhibit()
{
//    dbus = new QDBusInterface("org.gnome.SessionManager",
//                              "/org/gnome/SessionManager",
//                              "org.gnome.SessionManager",
//                              QDBusConnection::sessionBus());
    inhibitor_serial = 1;//默认inhibitor序号从1开始
}

usminhibit::~usminhibit(){}

quint32 usminhibit::addinhibit(QString app_id, quint32 toplevel_xid, QString reason, quint32 flags){
    if(app_id.isEmpty()){
        return -1;
    }
    if(reason.isEmpty()){
        return -1;
    }
    if(flags == 0){
        return -1;
    }

    quint32 cookie = generate_cookie();
    QString inhibitorName = "/org/gnome/SessionManager/inhibitor" + QString::number(get_next_inhibitor_serial());
    inhibit a(app_id,toplevel_xid,reason,flags,cookie,inhibitorName);
    hash.insert(cookie,a);
    qDebug()<<"app_id="<<app_id<<"; toplevel_xid="<<QString::number(toplevel_xid)<<"; reason="<<reason<<"; flag="<<QString::number(flags);
    return cookie;
}

uint usminhibit::generate_cookie(){
    quint32 cookie;
    do{
        cookie = QRandomGenerator::global()->bounded(1,4294967295);//std::numeric_limits<quint32>::max()
    }while (hash.contains(cookie)) ;
    return cookie;
}

uint usminhibit::uninhibit(quint32 cookie){
    uint flags = 0;
    QHash<quint32, inhibit>::iterator i = hash.find(cookie);
    while (i != hash.end() && i.key() == cookie) {
        flags = i->flags;
        i = hash.erase(i);
    }
    return flags;
}

QStringList usminhibit::getinhibitor(){
    QHashIterator<quint32, inhibit> i(hash);
    QStringList inhibitors;
    while (i.hasNext()) {
        i.next();
        QString name = i.value().inhibitorName;
        inhibitors<<name;
    }
    return inhibitors;
}


#include "usminhibit.moc"


