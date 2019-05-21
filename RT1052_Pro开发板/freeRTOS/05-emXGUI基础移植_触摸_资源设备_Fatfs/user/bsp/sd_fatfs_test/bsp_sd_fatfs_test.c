/**
******************************************************************
* @file   bsp_sd_fatfs_test.c
* @author  fire
* @version V1.0
* @date    2018-xx-xx
* @brief   SD卡驱动
******************************************************************
* @attention
*
* 实验平台:野火  i.MXRT1052开发板 
* 论坛    :http://www.firebbs.cn
* 淘宝    :http://firestm32.taobao.com
*
******************************************************************
*/
#include "fsl_debug_console.h"

#include "board.h"                      
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_sd.h"
#include "./bsp/sd_fatfs_test/bsp_sd_fatfs_test.h"
#include "fsl_sdmmc_host.h"

#include "emXGUI.h"

static int Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

/*
*函数功能：挂载文件系统
*参数：文件名（带有路径）如（/dir_1/hello.txt）
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_mount_test(FATFS* fileSystem)
{
  FRESULT error = FR_OK;
  char ch = '0';
  BYTE work[FF_MAX_SS];
  const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};
  FATFS* g_fileSystem = fileSystem;
  
  error = f_mount(g_fileSystem, driverNumberBuffer, 0U);
  if (error)
  {
    /*错误类型判断*/
    if(error == FR_NO_FILESYSTEM)//还没有文件系统
    {
      PRINTF("SD卡还没有文件系统，创建文件系统将会格式化您的SD卡。\r\n 确定是否继续？\r\n");
      PRINTF("输入‘y’确定格式化，输入‘n’取消\r\n");
      while(true)
      {
        ch = GETCHAR();
        PUTCHAR(ch);
        if(ch =='y'|| ch == 'Y')
        {
          /*为SD卡创建文件系统*/
#if FF_USE_MKFS
          PRINTF("\r\n制作文件系统...... SD卡容量越大，该过程持续时间越长。\r\n");
          if (f_mkfs(driverNumberBuffer, FM_ANY, 0U, work, sizeof work))
          {
            PRINTF("z制作文件系统失败.\r\n");
            while(1);
            
          }
          else
          {
            PRINTF("制作文件系统成功.\r\n");
            error = f_mount(g_fileSystem, driverNumberBuffer, 0U);
            if(error)
            {
              PRINTF("挂载文件系统失败\r\n");
              while(1);
            }
            else
            {
              break;
            }
            
          }
#endif /* FF_USE_MKFS */
        }
        else if(ch =='n'|| ch == 'N')
        {
          /*程序停止*/
         while(1);
        }
        
        PRINTF("输入‘y’确定格式化，输入‘n’取消\r\n");
      }  
    }
    else//其他错误，暂时不处理，直接退出函数
    {
      PRINTF("挂载文件系统失败\r\n");
      while(1);
    }
  }
  else 
  {
    PRINTF("挂载文件系统成功\r\n");
  }
  /*判断是否允许使用相对路径*/
#if (FF_FS_RPATH >= 2U)
  error = f_chdrive((char const *)&driverNumberBuffer[0U]);
  if (error)
  {
    PRINTF("Change drive failed.\r\n");
    while(1);
  }
  else
  {
    PRINTF("Change drive success.\r\n");
  }
#endif
  return error;
    
}



/*
*函数功能：创建一个空文件
*参数：文件名（带有路径）如（/dir_1/hello.txt）
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_touch_test(char* dir)
{
  FRESULT error = FR_OK;
  FIL g_fileObject ;   /* File object */
  PRINTF("\r\n创建“%s”文件......\r\n",dir);
  error = f_open(&g_fileObject, _T(dir), FA_CREATE_NEW);
  if (error)
  {
    if (error == FR_EXIST)
    {
      PRINTF("文件已经存在.\r\n");
    }
    else
    {
      PRINTF("创建文件失败\r\n");
      return error;
    }
    
  }
  else
  {
    PRINTF("创建文件成功 \r\n");
  }
  return error;
    
}

/*
*函数功能:创建一个目录
*函数参数：dir，目录路径。
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_mkdir_test(char* dir)
{
  FRESULT error;
  PRINTF("\r\n创建目录 “%s”......\r\n",dir);
  error = f_mkdir(_T(dir));
  if (error)
  {
    if (error == FR_EXIST)
    {
      PRINTF("目录已经存在\r\n");
    }
    else
    {
      PRINTF("创建目录失败.\r\n");
      return error;
    }
  }
  else
  {
    PRINTF("创建目录成功\r\n");
  }
  return error;
}


/*
*函数功能：以读和写的方式打开一个文件，如果文件不存在则创建文件并打开
*函数参数：dir，文件路径。fileObject，保存文件描述符。
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_open_test(char* dir,FIL* fileObject)
{
  FRESULT error = FR_OK;
  FIL* g_fileObject = fileObject;   /* File object */
  PRINTF("\r\n打开“%s”文件......\r\n",dir);
  error = f_open(g_fileObject, _T(dir), (FA_WRITE | FA_READ ));
  if (error)
  {
    if (error == FR_EXIST)
    {
      PRINTF("文件打开失败.\r\n");
    } 
  }
  else
  {
    PRINTF("文件打开成功 \r\n");
  }
 
  return error;
}


/*
*函数功能：关闭一个打开的文件
*函数参数：fileObject，保存文件描述符。
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_close_test(FIL* fileObject)
{
  FRESULT error = FR_OK;
  FIL* g_fileObject = fileObject;   /* File object */
  PRINTF("\r\n关闭文件\r\n");
  error = f_close(g_fileObject);
  if (error)
  {
    PRINTF("关闭文件失败\r\n");
    return error;
  }
  else
  {
    PRINTF("关闭文件成功\r\n");
  }
  return error;
}


/*
*函数功能：读取一个路径下的内容
*函数参数：dir，路径名。directory， 目录对象结构体，保存打开的目录信息。
fileInformation，文件信息结构体，保存文件信息。
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_readdir_test(char* dir,DIR* directory,FILINFO* fileInformation)
{
  FRESULT error = FR_OK;
  DIR* g_directory = directory; /* Directory object */
  FILINFO* g_fileInformation = fileInformation;
  
  
  PRINTF("\r\n列出“/dir_1”目录下的内容......\r\n");
  
  error = f_opendir(g_directory, dir);
  if (error)
  {
    PRINTF("打开路径失败\r\n");
    return error;
  }
  
  for (;;)
  {
    error = f_readdir(g_directory, g_fileInformation);
    
    /* To the end. */
    if ((error != FR_OK) || (g_fileInformation->fname[0U] == 0U))
    {
      break;
    }
    if (g_fileInformation->fname[0] == '.')
    {
      continue;
    }
    if (g_fileInformation->fattrib & AM_DIR)
    {
      PRINTF("文件夹 : %s\r\n", g_fileInformation->fname);
    }
    else
    {
      PRINTF("文件 : %s\r\n", g_fileInformation->fname);
    }
  }
  return error;
}


/*
*函数功能：读写测试
*函数参数：dir，路径名。data_write,指定将要写入文件的数据起始地址。data_read，从文件件读回的数据保存地址。
*返回值：错误状态，FR_OK 表示成功。
*/
FRESULT f_write_read_test(char* dir, void* data_write, void* data_read)
{
  FIL g_fileObject ;
  void* g_data_write = data_write;
  void* g_data_read = data_read;
  UINT g_bytesWritten;
  UINT g_bytesRead;
  FRESULT error = FR_OK;
  
  /*打开文件*/
  error = f_open_test(dir,&g_fileObject);
  if ((error))
  {
    PRINTF("打开文件失败. \r\n");
    return error;
  }

  /* 向文件内写入内容 */
  PRINTF("\r\n写入内容到“%s”文件\r\n",dir);
  error = f_write(&g_fileObject, g_data_write, sizeof(g_data_write), &g_bytesWritten);
  if ((error) || (g_bytesWritten != sizeof(g_data_write)))
  {
    PRINTF("写入文件失败. \r\n");
  }
  else
  {
    PRINTF("写入文件成功 \r\n");
  }
  
  /* 移动文件读写指针到文件开始处 */
  if (f_lseek(&g_fileObject, 0U))
  {
    PRINTF("设置文件读写指针失败 \r\n");
  }
  else
  {
    PRINTF("设置文件读写指针成功 \r\n");
  }
  
  /*读取"/dir_1/f_1.dat"文件的内容到 g_data_read 缓冲区*/
  PRINTF("读取“%s”文件\r\n",dir);
  memset(g_data_read, 0U, sizeof(g_data_read));
  error = f_read(&g_fileObject, g_data_read, sizeof(g_data_read), &g_bytesRead);
  if ((error) || (g_bytesRead != sizeof(g_data_read)))
  {
    PRINTF("读取文件失败 \r\n");
  }
  else
  {
    PRINTF("读取文件成功. \r\n");
  }

  
  /*比较读写内容是否一致*/
  PRINTF("比较读写内容\r\n");
  if (0 == Buffercmp((uint8_t*)g_data_write, (uint8_t*)g_data_read, sizeof(g_data_read)))
  {
    PRINTF("文件读写内容不一致\r\n");
  }
  else
  {
    PRINTF("文件读写内容一致\r\n");
  }
 
  /*关闭文件*/
  f_close_test(&g_fileObject);
  return error;
}

static int Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return 0;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return 1;
} 

/****************************END OF FILE**********************/
