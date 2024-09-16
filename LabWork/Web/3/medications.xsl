<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:med="http://example.com/medications"
    exclude-result-prefixes="xsl med">

    <!-- Описуємо, що створювати HTML -->
    <xsl:template match="/">
        <html>
            <head>
                <title>Каталог медичних препаратів</title>
                <style>
                    table {
                        width: 100%;
                        border-collapse: collapse;
                    }
                    table, th, td {
                        border: 1px solid black;
                    }
                    th, td {
                        padding: 8px;
                        text-align: left;
                    }
                    th {
                        background-color: #f2f2f2;
                    }
                </style>
            </head>
            <body>
                <h2>Каталог медичних препаратів</h2>
                <table>
                    <tr>
                        <th>Назва</th>
                        <th>Виробник</th>
                        <th>Форма</th>
                        <th>Дозування</th>
                        <th>Ціна</th>
                        <th>Валюта</th>
                        <th>Дата Виготовлення</th>
                        <th>Термін Придатності</th>
                    </tr>
                    <xsl:for-each select="//med:Препарат">
                        <tr>
                            <td><xsl:value-of select="med:Назва"/></td>
                            <td><xsl:value-of select="med:Виробник"/></td>
                            <td><xsl:value-of select="med:Форма"/></td>
                            <td><xsl:value-of select="med:Дозування"/></td>
                            <td><xsl:value-of select="med:Ціна"/></td>
                            <td><xsl:value-of select="med:Валюта"/></td>
                            <td><xsl:value-of select="med:ДатаВиготовлення"/></td>
                            <td><xsl:value-of select="med:ТермінПридатності"/></td>
                        </tr>
                    </xsl:for-each>
                </table>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
