/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTEXTOPTION_H
#define QTEXTOPTION_H

#include <QtCore/qnamespace.h>
#include <QtCore/qchar.h>
#include <QtCore/qmetatype.h>


QT_BEGIN_NAMESPACE


template <typename T> class QList;
struct QTextOptionPrivate;

class Q_GUI_EXPORT QTextOption
{
public:
    enum TabType {
        LeftTab,
        RightTab,
        CenterTab,
        DelimiterTab
    };

    struct Q_GUI_EXPORT Tab {
        inline Tab() : position(80), type(QTextOption::LeftTab) { }
        inline Tab(qreal pos, TabType tabType, QChar delim = QChar())
            : position(pos), type(tabType), delimiter(delim) {}

        inline bool operator==(const Tab &other) const {
            return type == other.type
                   && qFuzzyCompare(position, other.position)
                   && delimiter == other.delimiter;
        }

        inline bool operator!=(const Tab &other) const {
            return !operator==(other);
        }

        qreal position;
        TabType type;
        QChar delimiter;
    };

    QTextOption();
    /*implicit*/ QTextOption(Qt::Alignment alignment);
    ~QTextOption();

    QTextOption(const QTextOption &o);
    QTextOption &operator=(const QTextOption &o);

    inline void setAlignment(Qt::Alignment alignment);
    inline Qt::Alignment alignment() const { return Qt::Alignment(align); }

    inline void setTextDirection(Qt::LayoutDirection aDirection) { this->direction = aDirection; }
    inline Qt::LayoutDirection textDirection() const { return Qt::LayoutDirection(direction); }

    enum WrapMode {
        NoWrap,
        WordWrap,
        ManualWrap,
        WrapAnywhere,
        WrapAtWordBoundaryOrAnywhere
    };
    inline void setWrapMode(WrapMode wrap) { wordWrap = wrap; }
    inline WrapMode wrapMode() const { return static_cast<WrapMode>(wordWrap); }

    enum Flag {
        ShowTabsAndSpaces = 0x1,
        ShowLineAndParagraphSeparators = 0x2,
        AddSpaceForLineAndParagraphSeparators = 0x4,
        SuppressColors = 0x8,
        IncludeTrailingSpaces = 0x80000000
    };
    Q_DECLARE_FLAGS(Flags, Flag)
    inline void setFlags(Flags flags);
    inline Flags flags() const { return Flags(f); }

    inline void setTabStop(qreal tabStop);
    inline qreal tabStop() const { return tab; }

    void setTabArray(const QList<qreal> &tabStops);
    QList<qreal> tabArray() const;

    void setTabs(const QList<Tab> &tabStops);
    QList<Tab> tabs() const;

    void setUseDesignMetrics(bool b) { design = b; }
    bool useDesignMetrics() const { return design; }

private:
    uint align : 8;
    uint wordWrap : 4;
    uint design : 1;
    uint direction : 2;
    uint unused : 17;
    uint unused2; // ### Qt 6: remove unnecessary, extra 32 bits
    uint f;
    qreal tab;
    QTextOptionPrivate *d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QTextOption::Flags)

inline void QTextOption::setAlignment(Qt::Alignment aalignment)
{ align = aalignment; }

inline void QTextOption::setFlags(Flags aflags)
{ f = aflags; }

inline void QTextOption::setTabStop(qreal atabStop)
{ tab = atabStop; }

QT_END_NAMESPACE

Q_DECLARE_METATYPE( QTextOption::Tab )

#endif // QTEXTOPTION_H
