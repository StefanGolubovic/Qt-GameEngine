#include "sceneloader.h"
#include <QJsonDocument>
#include "mainwindow.h"
#include <string.h>
SceneLoader::SceneLoader()
{

}
void SceneLoader::setFilePath(std::string path){
    filePath = path;
}
std::string SceneLoader::getFilePath(){
    return filePath;
}
QGraphicsScene* SceneLoader::getScene() const{
    return scene;
}
bool SceneLoader::sceneSave(QGraphicsScene* scene){
    std::cout << "Usao"<<std::endl;
    QJsonArray listObjects;
    for(QGraphicsItem* item :scene->items()){

        QJsonObject objectToJson;

        if(item->type() == 1){

           Elipse* eObj = qgraphicsitem_cast<Elipse*>(item);
           objectToJson["name"] = "Elipse";
           objectToJson["angle"] = eObj->getAngle();
           objectToJson["scaleX"] = eObj->getScaleX();
           objectToJson["scaleY"] = eObj->getScaleY();
           objectToJson["locationX"] = eObj->getLocation().toPoint().rx();
           objectToJson["locationY"] = eObj->getLocation().toPoint().ry();

        }else if(item->type() == 2){
            Square* eObj = qgraphicsitem_cast<Square*>(item);
            objectToJson["name"] = "Square";
            objectToJson["locationX"] = eObj->scenePos().toPoint().rx();
            objectToJson["locationY"] = eObj->scenePos().toPoint().ry();

        }else if(item->type() == 3){
            Triangle* eObj = qgraphicsitem_cast<Triangle*>(item);
            objectToJson["name"] = "Triangle";
            objectToJson["locationX"] = eObj->scenePos().toPoint().rx();
            objectToJson["locationY"] = eObj->scenePos().toPoint().ry();

        }
        listObjects.push_back(objectToJson);
    }
    QFile file_obj("file_path.json");
    if(!file_obj.open(QIODevice::WriteOnly)){
        qDebug()<<"Failed to open "<<"file_path.json";
        return false;
    }

    QJsonDocument json_doc(listObjects);
    QString json_string = json_doc.toJson();
    file_obj.write(json_string.toLocal8Bit());
    file_obj.close();
    return true;
}
QJsonArray SceneLoader::sceneLoad(QString fileName){
    QFile file_obj(fileName);
    if(!file_obj.open(QIODevice::ReadOnly)){
        qDebug()<<"Failed to open "<< fileName;
    }
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();

    auto json_doc=QJsonDocument::fromJson(json_bytes);

    if(json_doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        exit(2);
    }
    if(!json_doc.isArray()){
        qDebug() << "JSON doc is not an array.";
        exit(1);
    }

    QJsonArray json_array = json_doc.array();

    if(json_array.isEmpty()){
        qDebug() << "The array is empty";
        exit(1);
    }
    QJsonArray listObjects;
    for(int i=0; i< json_array.count(); ++i){
        QJsonObject obj = json_array.at(i).toObject();
        listObjects.push_back(obj);
    }
    return listObjects;
}

