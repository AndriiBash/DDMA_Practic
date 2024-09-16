<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
    <xsl:output method="xml" indent="yes"/>

    <xsl:template match="/">
        <fo:root>
            <fo:layout-master-set>
                <fo:simple-page-master master-name="A4" page-width="210mm" page-height="297mm" margin="20mm">
                    <fo:region-body/>
                </fo:simple-page-master>
            </fo:layout-master-set>

            <fo:page-sequence master-reference="A4">
                <fo:flow flow-name="xsl-region-body">
                    <fo:block font-family="Arial" font-size="12pt" line-height="1.5">
                        <fo:block font-size="14pt" font-weight="bold" text-align="center" margin-bottom="10mm">
                            Каталог медичних препаратів
                        </fo:block>
                        <xsl:for-each select="//Препарат">
                            <fo:block>
                                <fo:inline font-weight="bold">Назва:</fo:inline> <xsl:value-of select="Назва"/><fo:block/>
                                <fo:inline font-weight="bold">Виробник:</fo:inline> <xsl:value-of select="Виробник"/><fo:block/>
                                <fo:inline font-weight="bold">Форма:</fo:inline> <xsl:value-of select="Форма"/><fo:block/>
                                <fo:inline font-weight="bold">Дозування:</fo:inline> <xsl:value-of select="Дозування"/><fo:block/>
                                <fo:inline font-weight="bold">Ціна:</fo:inline> <xsl:value-of select="Ціна"/> <xsl:value-of select="Валюта"/><fo:block/>
                                <fo:inline font-weight="bold">Дата Виготовлення:</fo:inline> <xsl:value-of select="ДатаВиготовлення"/><fo:block/>
                                <fo:inline font-weight="bold">Термін Придатності:</fo:inline> <xsl:value-of select="ТермінПридатності"/><fo:block margin-bottom="5mm"/>
                            </fo:block>
                        </xsl:for-each>
                    </fo:block>
                </fo:flow>
            </fo:page-sequence>
        </fo:root>
    </xsl:template>
</xsl:stylesheet>
