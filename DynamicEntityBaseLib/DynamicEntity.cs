using System.ComponentModel.DataAnnotations;

namespace DynamicEntityBaseLib
{
    public class DynamicEntity
    {
        [Key]
        public int ID { get; set; }

        
    }
    /*
     * 动态实体基类，所有实体继承此类，根据数据字典定义生成代码，编译，动态引用，动态加入数据库上下文
     * 另设实体状态类，所有实体与之关联，所有实体的ID均在状态类表中统一流水
     * 状态类负责保存实体的非业务数据。包含状态数据，任务流数据等
     * 
     */ 
      
}

