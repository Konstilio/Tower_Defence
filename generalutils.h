#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include <QSize>
#include <QPixmap>

class GeneralUtils
{
public:
    static GeneralUtils& Instance();

    const QPixmap &TiledTreeTowerPixmap();
    const QPixmap &TiledAcidTowerPixmap();
    const QPixmap &TiledIceTowerPixmap();
    const QPixmap &TiledStoneTowerPixmap();

    QSize GameViewSize() const;
    int TileSize() const;

private:
    QSize mp_GameViewSize;
    int mp_TileSize;

    QPixmap mp_TiledTreeTowerPixmap;
    QPixmap mp_TiledAcidTowerPixmap;
    QPixmap mp_TiledIceTowerPixmap;
    QPixmap mp_TiledStoneTowerPixmap;

    GeneralUtils();
    GeneralUtils(const GeneralUtils& Other) = delete;
    GeneralUtils& operator=(const GeneralUtils& Other) = delete;

    const QPixmap &GetTiledBitmap(QPixmap &CachedPixMap, const QString &Path);

};

#endif // GENERALUTILS_H
