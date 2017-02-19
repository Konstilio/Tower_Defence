#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include <QSize>
#include <QPixmap>

enum ECustomItemRole
{
    ECustomItemRole_Tower = 1
    , ECustomItemRole_Ammo = 2
    , ECustomItemRole_Enemy = 3
};

class GeneralUtils
{
public:
    static GeneralUtils& Instance();

    const QPixmap &TiledTreeTowerPixmap() const;
    const QPixmap &TiledAcidTowerPixmap() const;
    const QPixmap &TiledIceTowerPixmap() const;
    const QPixmap &TiledStoneTowerPixmap() const;
    const QPixmap &TiledSuperiorTowerPixmap() const;

    const QPixmap &TiledStartPixmap() const;
    const QPixmap &TiledEndPixmap() const;

    const QPixmap &TiledOutcastEnemyPixmap() const;
    const QPixmap &TiledOutlawEnemyPixmap() const;
    const QPixmap &TiledKatanamenEnemyPixmap() const;

    const QPixmap &AmmoAcidPixmap() const;
    const QPixmap &AmmoIcePixmap() const;
    const QPixmap &AmmoStonePixmap() const;
    const QPixmap &AmmoFirePixmap() const;

    QSize GameViewSize() const;
    int TileSize() const;

private:
    QSize mp_GameViewSize;
    int mp_TileSize;
    int mp_AmmoSize;

    // Tiled Towers
    mutable QPixmap mp_TiledTreeTowerPixmap;
    mutable QPixmap mp_TiledAcidTowerPixmap;
    mutable QPixmap mp_TiledIceTowerPixmap;
    mutable QPixmap mp_TiledStoneTowerPixmap;
    mutable QPixmap mp_TiledSuperiorTowerPixmap;

    // Ammo
    mutable QPixmap mp_AmmoAcidPixmap;
    mutable QPixmap mp_AmmoIcePixmap;
    mutable QPixmap mp_AmmoStonePixmap;
    mutable QPixmap mp_AmmoFirePixmap;

    // Ends
    mutable QPixmap mp_TiledStartPixmap;
    mutable QPixmap mp_TiledEndPixmap;

    //Enemy
    mutable QPixmap mp_TiledOutcastEnemyPixmap;
    mutable QPixmap mp_TiledOutlawEnemyPixmap;
    mutable QPixmap mp_TiledKatanamenEnemyPixmap;

    GeneralUtils();
    GeneralUtils(const GeneralUtils& Other) = delete;
    GeneralUtils& operator=(const GeneralUtils& Other) = delete;

    const QPixmap &getTiledBitmap(QPixmap &CachedPixMap, const QString &Path) const;
    const QPixmap &getAmmoBitmap(QPixmap &CachedPixMap, const QString &Path) const;

};

#endif // GENERALUTILS_H
