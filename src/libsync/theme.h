/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#ifndef _THEME_H
#define _THEME_H

#include <QObject>
#include "syncresult.h"

class QIcon;
class QString;
class QObject;
class QPixmap;
class QColor;
class QPaintDevice;

namespace OCC {

class SyncResult;

/**
 * @brief The Theme class
 * @ingroup libsync
 */
class OWNCLOUDSYNC_EXPORT Theme : public QObject
{
    Q_OBJECT
public:
    enum CustomMediaType {
        oCSetupTop,      // ownCloud connect page
        oCSetupSide,
        oCSetupBottom,
        oCSetupResultTop // ownCloud connect result page
    };

    /* returns a singleton instance. */
    static Theme* instance();

    ~Theme();

    /**
     * @brief appNameGUI - Human readable application name.
     *
     * Use and redefine this if the human readable name contains spaces,
     * special chars and such.
     *
     * By default, the name is derived from the APPLICATION_NAME
     * cmake variable.
     *
     * @return QString with human readable app name.
     */
    virtual QString appNameGUI() const;

    /**
     * @brief appName - Application name (short)
     *
     * Use and redefine this as an application name. Keep it straight as
     * it is used for config files etc. If you need a more sophisticated
     * name in the GUI, redefine appNameGUI.
     *
     * By default, the name is derived from the APPLICATION_SHORTNAME
     * cmake variable, and should be the same. This method is only
     * reimplementable for legacy reasons.
     *
     * Warning: Do not modify this value, as many things, e.g. settings
     * depend on it! You most likely want to modify \ref appNameGUI().
     *
     * @return QString with app name.
     */
    virtual QString appName() const;

    /**
     * @brief configFileName
     * @return the name of the config file.
     */
    virtual QString configFileName() const = 0;

#ifndef TOKEN_AUTH_ONLY
    static QString hidpiFileName(const QString &fileName, QPaintDevice *dev = 0);

    /**
      * the icon that is shown in the tray context menu left of the folder name
      */
    virtual QIcon   trayFolderIcon( const QString& ) const;

    /**
      * get an sync state icon
      */
    virtual QIcon   syncStateIcon( SyncResult::Status, bool sysTray = false ) const;

    virtual QIcon   folderDisabledIcon() const;
    virtual QIcon   folderOfflineIcon(bool systray = false) const;
    virtual QIcon   applicationIcon() const = 0;
#endif

    virtual QString statusHeaderText( SyncResult::Status ) const;
    virtual QString version() const;

    /**
     * Characteristics: bool if more than one sync folder is allowed
     */
    virtual bool singleSyncFolder() const;

    /**
     * When true, client works with multiple accounts.
     */
    virtual bool multiAccount() const;

    /**
    * URL to help file
    */
    virtual QString helpUrl() const { return QString::null; }

    /**
     * Setting a value here will pre-define the server url.
     *
     * The respective UI controls will be disabled
     */
    virtual QString overrideServerUrl() const;

    /**
     * The default folder name without path on the server at setup time.
     */
    virtual QString defaultServerFolder() const;

    /**
     * The default folder name without path on the client side at setup time.
     */
    virtual QString defaultClientFolder() const;

    /**
     * Override to encforce a particular locale, i.e. "de" or "pt_BR"
     */
    virtual QString enforcedLocale() const { return QString::null; }

    /** colored, white or black */
    QString systrayIconFlavor(bool mono) const;

#ifndef TOKEN_AUTH_ONLY
    /**
     * Override to use a string or a custom image name.
     * The default implementation will try to look up
     * :/client/theme/<type>.png
     */
    virtual QVariant customMedia( CustomMediaType type );

    /** @return color for the setup wizard */
    virtual QColor wizardHeaderTitleColor() const;

    /** @return color for the setup wizard. */
    virtual QColor wizardHeaderBackgroundColor() const;

    /** @return logo for the setup wizard. */
    virtual QPixmap wizardHeaderLogo() const;

    /**
     * The default implementation creates a
     * background based on
     * \ref wizardHeaderTitleColor().
     *
     * @return banner for the setup wizard.
     */
    virtual QPixmap wizardHeaderBanner() const;
#endif

    /**
     * The SHA sum of the released git commit
     */
    QString gitSHA1() const;

    /**
     * About dialog contents
     */
    virtual QString about() const;

    /**
     * Define if the systray icons should be using mono design
     */
    void setSystrayUseMonoIcons(bool mono);

    /**
     * Retrieve wether to use mono icons for systray
     */
    bool systrayUseMonoIcons() const;

    /**
     * @brief Where to check for new Updates.
     */
    virtual QString updateCheckUrl() const;

    /**
     * When true, the setup wizard will show the selective sync dialog by default and default
     * to nothing selected
     */
    virtual bool wizardSelectiveSyncDefaultNothing() const;
    /**
     * @brief Add an additional checksum header to PUT requests and compare them
     * if they come with GET requests.
     * This value sets the checksum type (SHA1, MD5 or Adler32) or is left empty
     * if no checksumming is wanted. In that case it can still be overwritten in
     * the client config file.
     */
    virtual QString transmissionChecksum() const;

    /**
     * Default option for the newBigFolderSizeLimit.
     * Size in MB of the maximum size of folder before we ask the confirmation.
     * Set -1 to never ask confirmation.  0 to ask confirmation for every folder.
     **/
    virtual qint64 newBigFolderSizeLimit() const;

    /**
     * Alternative path on the server that provides access to the webdav capabilities
     *
     * Attention: Make sure that this string does NOT have a leading slash and that
     * it has a trailing slash, for example "remote.php/webdav/".
     */
    virtual QString webDavPath() const;
    virtual QString webDavPathNonShib() const;

    /**
     * @brief Sharing options
     *
     * Allow link sharing and or user/group sharing
     */
    virtual bool linkSharing() const;
    virtual bool userGroupSharing() const;

    virtual bool forceSystemNetworkProxy() const;

    /**
     * @brief How to handle the userID
     *
     * @value UserIDUserName Wizard asks for user name as ID
     * @value UserIDEmail Wizard asks for an email as ID
     * @value UserIDCustom Specify string in \ref customUserID
     */
    enum UserIDType { UserIDUserName = 0, UserIDEmail, UserIDCustom };

    /** @return What to display as the userID (e.g. in the wizards) */
    virtual UserIDType userIDType() const { return UserIDType::UserIDUserName; }

    /**
     * @brief Allows to customize the type of user ID (e.g. user name, email)
     *
     * @note This string cannot be translated, but is still useful for
     *       referencing brand name IDs (e.g. "ACME ID", when using ACME.)
     * @return String to display when the user ID is inquired
     */
    virtual QString customUserID() const { return QString(); }

    /**
     * @return Demo string to be displayed when no text has been
     *         entered for the user id (e.g. mylogin@company.com)
     */
    virtual QString userIDHint() const { return QString(); }

protected:
#ifndef TOKEN_AUTH_ONLY
    QIcon themeIcon(const QString& name, bool sysTray = false) const;
#endif
    Theme();

signals:
    void systrayUseMonoIconsChanged(bool);

private:
    Theme(Theme const&);
    Theme& operator=(Theme const&);

    static Theme* _instance;
    bool _mono;
#ifndef TOKEN_AUTH_ONLY
    mutable QHash<QString, QIcon> _iconCache;
#endif
};

}
#endif // _THEME_H
