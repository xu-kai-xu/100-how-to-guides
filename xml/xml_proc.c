#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

uint32_t xml_parser_res(char *xml_name, char *file_name, uint32_t data_count)
{
    xmlDocPtr doc = xmlReadFile(xml_name, NULL, 0);
    if (doc == NULL) {
        printf("open xml file failed.\n");
        return 1; // err
    }

    //创建xpath上下文
    xmlXPathContextPtr xpath_ctx = xmlXPathNewContext(doc);
    if (xpath_ctx == NULL) {
        printf("create xpath context file failed.\n");
        xmlFreeDoc(doc);
        return 1; // err
    }

    // 执行xpath表达式
    xmlChar path_str[50] = {0};
    strcpy((char *)path_str, "/DATASET/DATA/item");

    xmlXPathObjectPtr xpath_obj = xmlXPathEvalExpression(path_str, xpath_ctx);
    if(xpath_obj == NULL) {
        printf("eval xpath expression failed.\n");
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        return 1; // err
    }

    // 提取bcp文件名
    xmlNodePtr node_bcp = xpath_obj->nodesetval->nodeTab[1];
    xmlChar *bcp_name = xmlGetProp(node_bcp, (xmlChar*)"file_name");
    printf("bcp_name: %s\n", bcp_name);
    if (strcmp(bcp_name, file_name) != 0) {
        xmlFree(bcp_name);
        // xmlFreeNode(node_bcp);
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    // 提取记录行数
    printf("now line_nums\n");
    xmlNodePtr node_lines = xpath_obj->nodesetval->nodeTab[0];
    xmlChar *lines = xmlGetProp(node_lines, (xmlChar *)"line_num");
    char count[5] = {0};
    if (sprintf(count, "%u", data_count) < 0) {
        xmlFree(bcp_name);
        xmlFree(lines);
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }
    if (strcmp(count, lines) != 0) {
        xmlFree(bcp_name);
        xmlFree(lines);
        xmlXPathFreeObject(xpath_obj);
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return 1;
    }

    xmlFree(bcp_name);
    xmlFree(lines);
    xmlXPathFreeObject(xpath_obj);
    xmlXPathFreeContext(xpath_ctx);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return 0;

}

int main()
{
    char xml_name[] = "/home/xukk/clang/xml/test1.xml";
    char file_name[] = "random1.txt";
    int16_t data_count = 300;

    uint32_t ret = xml_parser_res(xml_name, file_name, data_count);
    if (ret == 0) {
        printf("xml parser success.\n");
    } else {
        printf("xml parser failed.\n");
    }
    return 0;
}