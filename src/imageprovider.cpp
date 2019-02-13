#include "imageprovider.h"

#include <QFile>
#include <QMetaObject>
#include <QStandardPaths>
#include <QtCore/QDebug>
#include <QtCore/QWaitCondition>
#include <QDir>

#include "jobs/mediathumbnailjob.h"

#include "connection.h"

using QMatrixClient::MediaThumbnailJob;

ImageProvider::ImageProvider(QObject* parent)
    : QObject(parent),
      QQuickImageProvider(
          QQmlImageProviderBase::Image,
          QQmlImageProviderBase::ForceAsynchronousImageLoading) {}

QImage ImageProvider::requestImage(const QString& id, QSize* pSize,
                                   const QSize& requestedSize) {
  if (id.count("/") != 1) {
    qWarning() << "ImageProvider: won't fetch an invalid id:" << id
               << "doesn't follow server/mediaId pattern";
    return {};
  }

  QUrl tempfilePath = QUrl::fromLocalFile(
      QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imagecache/" +
      QString(id).replace("/", "-") + "-" + QString::number(requestedSize.width()) + "x" +
      QString::number(requestedSize.height()) + ".png");

  QImage cachedImage;
  if (cachedImage.load(tempfilePath.toLocalFile())) {
    if (pSize != nullptr) *pSize = cachedImage.size();
    return cachedImage;
  }

  if (m_connection == nullptr) return QImage();

  MediaThumbnailJob* job = nullptr;
  QReadLocker locker(&m_lock);

  QMetaObject::invokeMethod(
      m_connection,
      [=] { return m_connection->getThumbnail(id, requestedSize); },
      Qt::BlockingQueuedConnection, &job);
  if (!job) {
    qDebug() << "ImageProvider: failed to send a request";
    return {};
  }
  QImage result;
  {
    QWaitCondition condition;  // The most compact way to block on a signal
    job->connect(job, &MediaThumbnailJob::finished, job, [&] {
      result = job->thumbnail();
      condition.wakeAll();
    });
    condition.wait(&m_lock);
  }

  if (pSize != nullptr) *pSize = result.size();

  QDir dir(QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/imagecache/");
  if (!dir.exists()) dir.mkpath(".");

  result.save(tempfilePath.toLocalFile());

  return result;
}
