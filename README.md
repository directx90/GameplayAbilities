# GameplayAbilities
---

# Character
>改造Character
1. 在Build.cs里的PublicDependencyModuleNames添加 "GameplayAbilities","GameplayTags","GameplayTasks"
2. IAbilitySystemInterface ： 继承并实现GetAbilitySystemComponent接口
3. AbilitySystemComponent : 技能组件
4. GiveAbility : 设定技能
5. Try Active Abilities by Tag : 通过标签激活技能
6. Try Active Abilities by Class : 通过类激活技能


# GameplayTag
> 技能运作的基石
1.  很多的Crash
2.  保存为DefaultGameplayTags.ini
3.  Import Tags from Config : 从配置文件导入
4.  Gameplay Tag Table List  Gameplay Tag Table Row : 从DataTable导入
5.  Add New Gameplay Tag : 添加新的Tag
6.  Add New Tag Source : 添加新的配置文件
7.  Gameplay Tag List : 显示所有的Tag
8.  Restricted Config Files : 限制的配置文件
9.  Restricted Config Name : 限制的配置文件名
10. Owners : 拥有者
11. Allow non-restricted children : 是否允许添加子节点
12. Restrictred Tag List : 显示限制的Tag，不能删除，只能通过手动修改配置文件
13. Gameplay Tag Container : Tag的数组结构，C++:FGameplayTag,FGameplayTagContainer
14. Gameplay Tag Operations : 
    1.  Matches Tag
    2.  Matches Any Tags
    3.  Has Tag
    4.  Has Any Tags
    5.  Has All Tags
    6.  Exact Match
15. Gameplay Tag Query : Tag查询操作，C++:FGameplayTagQuery
    1.  All Expressions Match ：所有的表达式都返回True
    2.  Any Expressions Match : 任意一个表达式返回True
    3.  No Expressions Match : 所有表达式返回False
    4.  All Tags Match : 所有都匹配
    5.  Any Tags Match : 任意Tag匹配
    6.  No Tags Match : 任意Tag都不匹配
16. IGameplayTagAssetInterface : Actor继承接口
    1.  virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override : 实现接口
    2.  Get All Actors Of Class Matching Tag Query : 使用Blueprint节点


# GameplayAbility
> 触发技能后主要逻辑
1.  启用Gameplay Abilities : Plugins Gameplay
2.  创建GameplayAbility 
3.  UGameplayAbility : C++基类
4.  Event ActiveAbility : 技能激活时
5.  Event OnEndAbility : 技能结束时
6.  Tags
    1.  Ability Tags : 技能拥有的标签
    2.  Cancel Abilities with Tag : 激活此技能后，将取消拥有这些标签的技能
    3.  Block Abilities with Tag : 激活此技能后，将阻止拥有这些标签的技能
    4.  Activation Owned Tags : 激活此技能后，将拥有这些附带的标签
    5.  Activation Required Tags : 激活技能时需要的标签
    6.  Activation Blocked Tags : 阻碍激活技能的标签
    7.  Source Required Tags : 源头拥有这些标签才能激活此技能
    8.  Source Blocked Tags : 源头拥有这些标签将阻碍激活此技能
    9.  Target Required Tags : 目标拥有这些标签才能激活此技能
    10.  Target Blocked Tags : 目标拥有这些标签将阻碍激活此技能
7.  Advanced
    1.  Replication Policy : 是否使用网络同步
    2.  Instancing Policy : 实例化策略
        1.  Non Instanced : 不实例化技能，特点：高效，通过Class Default Object创建。带来的限制： 限制某些功能，没有变量，没有状态，没有Task，不能绑定代理，不能进行网络复制，没有RPC。用于多人频发的技能。测试会Crash。
        2.  Instanced Per Actor : 每个Actor实例化一个技能，只创建一次
        3.  Instanced Per Executation : 每次释放实都实例化技能，每次都创建，最消耗。
    3.  Server Respects Remote Ability Cancellation : 如果为True，服务端会接受客户端的取消操作，客户端总是接受服务端的取消操作。
    4.  Retrigger Instanced Ability : 当Instancing Policy为Instanced Per Actor时才有效，如果为True,激活已经激活的技能，将会结束此技能然后重新激活，如果为False,激活已经激活的技能，将会失败。
    5.  Net Execution Policy : 网络执行策略
        1.  Local Predicted : 客户端执行，拥有较好的响应速度和准确性，释放技能时本地立即执行，但是服务端有最终的决定权，可以覆盖客户端的结果。只要客户端不出错就会非常的流畅。
        2.  Local Only : 客户端执行，适用于单机游戏。
        3.  Server Initiated : 服务器执行，然后通过网络复制同步到客户端，结果最准确，但是会有延迟。
        4.  Server Only : 服务器执行，不进行网络复制，但是受此技能影响的其他变量将会同步到客户端。
8. Costs : 消耗，例如：消耗蓝，魔法，体力，血量，怒气等。 通过CommitAbility使用。
    1. Cost Gameplay Effect Class : Gameplay Effect对象
9.  Triggers : 通过某些途径触发标签，
    1.  Trigger Tag : 触发的标签
    2.  Trigger Source : 触发来源的种类
        1. Gameplay Event : 使用Send Gameplay Event to Actor节点，可以携带参数
        2. Owned Tag Added : 添加标签时触发，先于源标签激活
        3. Owned Tag Present : 添加标签时触发，当标签被移除时，此触发技能也会结束。先于源标签激活。
10. Cooldowns : CD
    1. Cooldown Gameplay Effect Class :  Gameplay Effect对象
11. Blueprint逻辑
    1.  GiveAbility ：在C++层调用GiveAbility
    2.  Try Activate Ability by Class : 通过类型激活技能
    3.  Try Activate Ability by Tag : 通过标签激活技能
    4.  CommitAbility : 提交技能，检查并应用消耗与CD
    5.  CommitAbilityCooldown : 提交技能，只检查并应用CD
    6.  CommitAbilityCost : 提交技能，只检查并应用消耗
    7.  EndAbility : 在Event ActiveAbility 后面调用，调用后会出发Event OnEndAbility


# GameplayEffect
> 没有逻辑，通常是配置
1.  Gameplay Effect
    1.  Duration Policy : 持续策略
        1.  Instant : 瞬时
        2.  Infinite : 永久
        3.  Has Duration : 持续时间，单位：秒
            1.  Magnitude Calculation Type : 时长计算种类
                1.  Scalable Float : 可扩展的浮点数。Raw Value : 基础数值；Curve Table : 读取配置表，最终的结果是根据等级读取并相乘
                2.  Attribute Based : 基于属性，公式: a*(x+b)+c
                    1.  Coefficient : a
                    2.  Pre Multiply Additive Value : b
                    3.  Post Multiply Additive Value : c
                    4.  Backing Attribute : 支持属性
                        1.  Attribute to Capture : 指定的属性，FGameplayAttributeData类型，公式里的x，未指定将变成无限
                        2.  Attribute Source : 属性源。Source和Target  
                        3.  Snapshot : 是否进行快照。例如火球的伤害是10，当火球发出时就应进行快照，因为释放者的属性可能会在火球飞行的过程中被修改，不能让其影响已经释放了的火球。
                    5.  Attribute Curve : 属性配置。如果制定了配置，就会读取配置里的数值，公式变成 a*(x*y+b)+c，公式里的y
                        1.  Curve Table : 配置表
                        2.  Row Name : 行的名字
                    6.  Attribute Calculation Type : 属性计算的类型
                        1.  Attribute Magnitude : 使用计算后的结果
                        2.  Attribute Base Value : 和上面一样 ？
                        3.  Attribute Bonus Magnitude : x不会用Attribute的值
                    7.  Source Tag Filter : 不知
                    8.  Target Tag Filter : 不知
                3.  Custom Calculation Class : 自定计算，能够使用Blueprint或C++里的多个属性
                    1.  Calculation Class : 指定用于计算的类，需要实现CalculateBaseMagnitude方法
                    2.  Final Lookup Curve : 最终校正。如果制定有效，将会进一步通过CurveTable计算
                4.  Set by Caller : 不知。 通过调用者设置，如果指定了标签，先通过标签查找，再通过名字查找
                    1.  Data Name : 不知。 通过名字查找 
                    2.  Data Tag : 不知。 通过标签查找
    2.  Modifiers : 修改器列表
        1.  Attribute : 修改的属性
        2.  Modifier Op : 操作
            1.  Add : +
            2.  Multiply : *
            3.  Divide : /
            4.  Override : 覆写
        3.  Modifier Magnitude : 数据的计算， 同Duration Magnitude
        4.  Source Tags : 不知。 需要源遵循的标签规则
        5.  Target Tags : 不知。 需要目标遵循的标签规则
    3.  Executions : 自定义的执行代码
        1.  Calculation Class : Gameplay Effect Execution Calculation类，需要实现Execute方法
        2.  Conditional Gameplay Effects : 如果执行计算成功，将应用额外的效果到目标，如果未指定计算类，将总是应用额外的效果到目标。
            1.  Effect Class : 需要应用的效果
            2.  Required Source Tags : 需要源拥有的标签
2.  Period : 周期
    1.  Period : 周期时长，表示在持续内以固定周期执行效果
    2.  Execute Periodic Effect on Application : 如果为True在应用的时候执行一次，然后固定周期执行一次，如果为False在应用时不会执行，后面固定周期执行一次。
3.  Application : 应用
    1.  Chance to Apply to Target : 应用此效果的概率，取值范围:[0,1]
    2.  Application Requirement : 应用依赖数组，自定义Gameplay Effect Custom Application Requirement类，需要实现Can Apply Gameplay Effect方法
4.  Stacking : 堆栈
    1.  Stacking Type : 堆栈类型
        1.  None : 不叠加，每次应用都是独立的
        2.  Aggregate by Source : 以释放者为堆栈
        3.  Aggregate by Target : 以接受者为堆栈
    2.  Stack Limit Count : 堆栈大小
    3.  Stack Duration Refresh Policy : 刷新持续时间的策略
        1.  Refresh on Successful Application : 当成功应用时刷新持续时间
        2.  Nerver Refresh : 从不刷新持续时间
    4.  Stack Period Reset Policy : 重置周期的策略
        1.  Reset on Successful Application : 当成功应用是重置周期
        2.  Never Reset : 从不重置周期
    5.  Stack Expiration Policy : 效果到期的策略，只对有持续时间的效果有效
        1.  Clear Entire Stack : 当效果到期后清空整个堆栈
        2.  Remove Single Stack and Refresh Duration : 移除单个到期的效果，并刷新时间，即堆栈减1，重新开始
        3.  Refresh Duration : 直接刷新时间，相当于无限的效果，需要通过回调（Callback)来手动减少堆栈
5.  Overflow : 溢出
    1.  Overflow Effects : 当堆栈溢出时添加的效果，例如：当受到10个冰雪技能后，受到一个冰冻效果
    2.  Deny Overflow Application : 拒绝溢出时应用，为True时表示当堆栈满了时将拒绝继续添加效果，从而导致无法刷新持续时间
    3.  Clear Stack on Overflow : 当Deny Overflow Application为True时才有效。溢出会进行清空
6.  Expiration : 持续时间到期
    1.  Premature Expiration Effect Classes : 当持续效果被过早终结时使用的效果
    2.  Routine Expiration Effect Classes : 当持续效果自然终结时使用的效果
7.  Display : 视觉显示，特效，音效，UI。主要使用Gameplay Cue
    1.  Require Modifier Success to Trigger Cues : 为True表示当Modifiers全部执行成功时才会显示视觉效果
    2.  Suppress Stacking Cues : 为True表示只在第一个进栈的效果触发
    3.  Gameplay Cues : 
        1.  Magnitude Attribute : 指定的属性,如果未指定则使用等级
        2.  Min Level -  Max Level : 用于归一化等级，控制效果有多强
        3.  Gameplay Cue Tags : 拥有专门的Tag，GameplayCue.XXX.YYY
    4.  UIData : 通过UI表示数据等，server-only不可用，GameplayEffectUIData类。
8.  Tags : 标签
    1.  GameplayEffectAssetTag : 效果拥有的标签，并不会应用到Actor上，FInheritedTagContainer类型，
        1.  Combined Tags : 和Parent组合后的标签
        2.  Added : 需要添加的标签
        3.  Removed : 需要从Parent里移除的标签
    2.  GrantedTags : 携带的标签，效果应用时将会应用到Actor
    3.  Ongoing Tag Requirements : 一但效果应用，这些标签将会决定效果开启还是关闭，效果任然可以被应用但是可以被关闭然后什么都不做。FGameplayTagRequirements类型
        1.  Require Tags : 需要的标签
        2.  Ignore Tags : 不能有的标签
    4.  Application Tag Requirements : 应用效果需要的标签，如果没通过将会应用失败，FGameplayTagRequirements类型。
    5.  Remove Gameplay Effects with Tags : 应用效果时需要移除的标签
9.  Immunity : 免疫。不知
10.  Granted Abilities : 附带的技能
    1.   Ability : 技能类
    2.   Level : 技能的等级
    3.   Input ID : 绑定的InputID
    4.   Remove Policy : 移除策略，当效果被移除是，附带的技能如何移除
        1.   Cancel Ability Immediately : 立即取消移除
        2.   Remove Ability on End : 等待技能完成，然后移除
        3.   Do Nothing : 不移除，让其自生自灭
11. ApplyGameplayEffectToTarget : 通过此Blueprint节点使用效果


# GameplayCue
>用于表现特效，音效
1. Gameplay Cue
    1. Gameplay Cue Tag : 标签
    2. Auto Attach to Owner : 为True时将在BeginPlay时附加到Actor，有消耗，在需要用时才设为True
    3. Is Override : 不知
    4. Unique Instance Per Instigator : 当多个释放者应用Cue到同一个目标时是否创建单独的实例。例如：在目标处播放一个特效或声音不用创建多个实例；创建一个连接释放者和目标的光束就需要创建单独的实例。
    5. Unique Instance Per Source Object : 当同一个释放者应用Cue到多个目标时是否创建单独的实例
    6. Allow Multiple on Active Events : 是否能够重复触发OnActive事件，出现在只有一个实例的情况下
    7. Allow Multiple While Active Events : 是否能够重复触发WhileActive
    8. Num Preallocated Instances : 预分配实例的数量
2.  Cleanup : 
    1.  Auto Destroy on Remove : 执行OnRemove后这个Actor对象将被删除或者回收
    2.  Auto Destroy Delay : 当Auto Destroy on Remove为True的情况下延迟删除的时间
    3.  Warn if Timeline is Still Running : 当回收时如果还有Timeline运行，将会发出警告。依然会停止Timeline
    4.  Warn if Latent Action Is Still Running : 当回收时如果还有Latent任务运行，将会发出警告。依然会停止Latent
3.  Function : 可以在这些方法里编写逻辑，比如播特效和音效
    1.  OnActive : 激活时
    2.  WhileActive :  激活时，还未被应用
    3.  OnExecute : 效果执行时，可能是瞬时的或者周期性的
    4.  OnRemove : 移除时
   

# AttributeSet
> 属性集，必须使用C++
1.  FGameplayAttributeData : 属性类型，推荐使用此类型而不是float
2.  PreAttributeChange : 修改属性之前执行，例如：修改血量时进行限制，HP=Clamp(0,MaxHP);
3.  PreAttributeBaseChange : 修改属性基础值之前执行，属性为FGameplayAttributeData才有效
4.  PreGameplayEffectExecute ： 修改属性时执行检查，如果返回True则允许修改，返回False终止修改操作。注意：在效果应用时不会执行，在效果执行时才会执行。
5.  PostGameplayEffectExecute ： 修改属性后执行，注意：在效果应用时不会执行，在效果执行时才会执行。
6.  GetLifetimeReplicatedProps ： DOREPLIFETIME_CONDITION_NOTIFY将属性设置为网络同步
7.  ReplicatedUsing : OnRep_XXXAttribute
8.  InitStats ： 初始化属性，可以关联DataTable
9.  FGameplayAttribute ：可以通过宏来进行声明和定义


# UGameplayEffectExecutionCalculation
>自定义计算
1. UGameplayEffectExecutionCalculation : 继承此类
2. Execute_Implementation ：实现此接口，Blueprint实现Execute方法
3. DECLARE_ATTRIBUTE_CAPTUREDEF : 声明宏
4. DEFINE_ATTRIBUTE_CAPTUREDEF ：定义宏
5. RelevantAttributesToCapture : 将需要属性添加到此列表
6. InvalidScopedModifierAttributes : 将需要属性添加到此列表
7. Attributes : 
    1. Requires Passed in Tags : 是否需要以参数的方式传入标签
    2. Invalid Scoped Modifier Attributes : 不需要的属性列表，加入此列表里的属性将不会显示在效果界面
    3. Relevant Attributes to Capture : 需要显示的属性


# GameplayEvent
>用于事件的出发，可以携带参数
1.  FGameplayTag EventTag ：事件标签
2.  const AActor* Instigator : 释放者
3.  const AActor* Target : 目标
4.  const UObject* OptionalObject : 可携带其他数据
5.  const UObject* OptionalObject2 : 同上
6.  FGameplayEffectContextHandle ContextHandle : 效果上下文，包含其他参数
7.  FGameplayTagContainer InstigatorTags : 触发事件时释放者的标签，因为后面释放者的标签可能会变
8.  FGameplayTagContainer TargetTags : 同上，目标标签
9.  float EventMagnitude : 浮点值
10. FGameplayAbilityTargetDataHandle TargetData : 目标的数据
11. SendGameplayEventToActor : 出发事件的方法，位于UAbilitySystemBlueprintLibrary
12. SendGameplayEvent : 位于UGameplayAbility



# 参考
* ## 中文教程
    >[Unreal Engine 4（虚幻UE4） GameplayAbilities插件入门教程] https://www.cnblogs.com/JackSamuel/tag/GameplayAbility%E6%8F%92%E4%BB%B6/

* ## 视频教程
    >[WTF Is? Gameplay Tags in Unreal Engine 4 ( UE4 )] https://www.youtube.com/watch?v=e2rdXo408Q0

    >[Intro to Gameplay Abilities in Unreal Engine 4] https://www.youtube.com/watch?v=Ev2P6BTUxN0

    >[Intro to the Unreal Engine Gameplay Abilities Module - Unreal Sydney Meetup] https://www.youtube.com/watch?v=OyiweL2nPac

    >[Tutorial: Custom Abilities in UE4's Action RPG Game (C++ / Blueprint)] https://www.youtube.com/watch?v=Tu5AJKNe1Ok

* ## 官方文档
    >[Gameplay Tags] https://docs.unrealengine.com/en-us/Gameplay/Tags

    >[Gameplay Ability System] https://docs.unrealengine.com/Gameplay/GameplayAbilitySystem/GameplayAbilities

* ## 论坛
    >[GameplayAbilities and You] https://forums.unrealengine.com/community/community-content-tools-and-tutorials/110113-gameplayabilities-and-you
    
    >[Comprehensive GameplayAbilities Analysis Series] https://forums.unrealengine.com/community/community-content-tools-and-tutorials/116578-comprehensive-gameplayabilities-analysis-series?143688-Comprehensive-GameplayAbilities-Analysis-Series=

* ## 案例工程
    >[Action RPG Game] https://docs.unrealengine.com/en-us/Resources/SampleGames/ARPG

    >[MCGameplayAbilities] https://github.com/michaeltchapman/MCGameplayAbilities

    >[Unreal_GameplayAbilities_FirstPerson] https://github.com/DavidENishball/Unreal_GameplayAbilities_FirstPerson

    >[GASContent] https://github.com/Pantong51/GASContent#gas-intro









