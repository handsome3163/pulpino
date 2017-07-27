/* Copyright (C) 2017 ETH Zurich, University of Bologna
 * All rights reserved.
 *
 * This code is under development and not yet released to the public.
 * Until it is released, the code is under the copyright of ETH Zurich and
 * the University of Bologna, and may contain confidential and/or unpublished
 * work. Any reuse/redistribution is strictly forbidden without written
 * permission from ETH Zurich.
 *
 * Bug fixes and contributions will eventually be released under the
 * SolderPad open hardware license in the context of the PULP platform
 * (http://www.pulp-platform.org), under the copyright of ETH Zurich and the
 * University of Bologna.
 */
/////////////////////////////////////////////////////////
// includes
/////////////////////////////////////////////////////////
#include "mlGemm.h"
#include "bar.h"
#include "utils.h"
#include "bench.h"

/////////////////////////////////////////////////////////
// shared globals
/////////////////////////////////////////////////////////
  __attribute__ ((section(".heapsram"))) static const float fv0[400] = { 8.89247131F, 7.50677824F, 9.94982147F,
    6.09410763F, 9.38635063F, 3.01820636F, 7.43147373F, 8.97153187F, 5.09758377F,
    7.48111486F, 9.07107925F, 2.84900951F, 1.61161745F, 4.4398F, 5.4628706F,
    8.59227276F, 3.35095954F, 9.54609776F, 6.88506079F, 0.735066533F,
    0.59213382F, 2.17626238F, 7.98191404F, 5.62968063F, 5.49932766F, 7.76460695F,
    8.40954113F, 7.35757923F, 3.49168038F, 9.32409763F, 4.28206396F, 8.03502274F,
    3.05342674F, 9.78941345F, 2.20663691F, 6.13623953F, 7.28104591F, 6.69313431F,
    2.80221081F, 6.89461184F, 7.62704754F, 5.57031107F, 3.15670323F, 9.93972778F,
    6.2677803F, 3.15189457F, 2.17198062F, 4.02478313F, 0.222307399F, 7.06391954F,
    4.35831308F, 0.150140569F, 4.2003026F, 6.03485823F, 0.24239023F, 2.56900239F,
    0.740730941F, 6.35269785F, 3.24030304F, 3.35353303F, 5.26203632F,
    6.06928778F, 2.43750787F, 6.29853916F, 1.68021381F, 9.44331932F, 2.62257457F,
    2.97152114F, 4.95683861F, 0.539529085F, 1.99947155F, 8.62303829F,
    2.22101331F, 0.00570779108F, 0.733338654F, 3.4409678F, 0.61466229F,
    4.26956224F, 0.0139661897F, 1.72916746F, 9.96433926F, 1.92268395F,
    9.39096355F, 1.45160341F, 4.96529388F, 6.23136568F, 3.85536F, 8.06283951F,
    3.52602267F, 0.592366874F, 9.99508667F, 4.89905882F, 0.631627083F,
    2.41008162F, 3.82525063F, 6.63644743F, 0.833860874F, 8.98109245F,
    6.11819553F, 4.19543362F, 6.46676874F, 9.26230621F, 0.811671555F,
    2.17720079F, 6.09357595F, 0.357289165F, 4.68230295F, 5.20453215F,
    7.63421345F, 2.27793765F, 3.37815022F, 2.27287626F, 3.22333288F, 1.6743114F,
    3.75289226F, 4.87764835F, 3.91026545F, 5.41200066F, 4.73076F, 1.00765F,
    2.59467196F, 4.94100809F, 4.37650824F, 2.51459599F, 0.71309495F, 4.91243505F,
    0.951248884F, 5.44111967F, 3.21189475F, 5.69402885F, 8.74080181F,
    1.98880208F, 0.469484776F, 3.93977523F, 6.00458241F, 2.61358333F, 5.14937F,
    2.02925301F, 7.2279F, 5.24082851F, 8.92702484F, 7.87473249F, 4.42631435F,
    2.99043226F, 3.42508674F, 6.04146051F, 3.83839774F, 4.28633213F, 2.68180752F,
    6.68000698F, 5.75224495F, 9.84633732F, 6.17245865F, 8.70508289F, 4.12925816F,
    0.348981321F, 5.77439642F, 1.76397169F, 1.23106277F, 8.07276726F,
    8.86107254F, 4.16618109F, 2.63971019F, 3.89775372F, 8.8918457F, 7.1322484F,
    6.1985631F, 7.20123959F, 7.65737104F, 6.2974472F, 9.32337379F, 2.64015222F,
    7.12931681F, 0.534368217F, 5.61906815F, 8.50285244F, 6.92269945F, 4.2837F,
    9.98289776F, 9.44441223F, 7.49933815F, 9.51518345F, 1.79286146F, 1.30675685F,
    8.9772377F, 7.31424952F, 7.15101576F, 2.63648129F, 9.7994194F, 9.88946342F,
    5.60708284F, 0.67217809F, 3.67933702F, 9.92470551F, 3.4972856F, 4.41530228F,
    5.86499214F, 7.2768712F, 7.60969973F, 6.43873F, 9.24814224F, 0.896307588F,
    5.57273531F, 0.857632041F, 9.22881222F, 6.33554459F, 3.98309541F,
    6.21944046F, 1.95722485F, 9.80955124F, 0.677073896F, 7.926085F, 3.57422614F,
    5.10305309F, 7.92188883F, 1.13765597F, 9.85270786F, 0.493414104F,
    7.86926413F, 9.90545082F, 2.41171169F, 5.97673368F, 3.23051858F, 3.29411697F,
    2.99968028F, 6.69573164F, 6.8696413F, 4.34254313F, 5.26335144F, 5.70597792F,
    7.4641614F, 5.22347927F, 0.36766091F, 0.497000515F, 2.28723884F, 5.77072716F,
    5.38167524F, 9.40537262F, 8.28113079F, 5.35567141F, 9.55508232F, 3.04585242F,
    2.13108301F, 3.15482664F, 5.52192879F, 2.0762372F, 6.1135006F, 9.40994835F,
    5.79665422F, 4.39501381F, 0.434757F, 0.966745675F, 6.69949675F, 9.34417534F,
    9.15470409F, 3.894485F, 7.04110765F, 3.91377163F, 5.32623672F, 2.5203383F,
    7.01072407F, 9.68191528F, 9.87186337F, 0.117573746F, 3.21994376F,
    5.63604403F, 6.15627098F, 1.42448366F, 5.56172848F, 7.80962563F, 5.45863247F,
    9.71471F, 4.35854F, 1.18818069F, 7.61484385F, 6.84083223F, 0.642780423F,
    4.27189207F, 4.42977285F, 2.22371197F, 1.0346781F, 2.31356192F, 0.487405866F,
    9.07765388F, 1.19750488F, 1.52586567F, 8.02355194F, 9.8738451F, 5.86217976F,
    3.39854145F, 9.88938427F, 7.5720706F, 7.30649805F, 1.22116768F, 7.46414709F,
    5.38286638F, 4.90236282F, 2.12953186F, 5.6801877F, 7.79776335F, 9.59862614F,
    6.40740538F, 2.61807251F, 8.1376543F, 4.36685658F, 7.35844135F, 9.84192944F,
    7.1264286F, 2.91950893F, 3.67091131F, 3.12134862F, 9.53191471F, 8.06195F,
    9.78407097F, 6.99984455F, 2.86294389F, 3.29560399F, 9.45867729F, 9.22726059F,
    4.78539228F, 7.14526606F, 2.20331573F, 8.41199303F, 6.95923615F, 6.63209057F,
    7.52412128F, 2.02850199F, 3.32639432F, 4.37211704F, 4.39989185F, 8.03530693F,
    1.57466829F, 8.73280525F, 9.18287086F, 7.35958767F, 4.26807308F, 3.21823025F,
    5.40609121F, 3.19649339F, 3.3390367F, 9.15818787F, 9.49570465F, 1.05489659F,
    8.38048077F, 4.78661F, 9.8017149F, 8.69108486F, 5.66567707F, 1.95259035F,
    9.70500469F, 3.81893754F, 4.36489677F, 5.41190481F, 8.04623508F, 2.56636477F,
    8.355937F, 7.71251345F, 7.23137522F, 1.64480519F, 4.49124813F, 7.73742628F,
    6.92694378F, 0.0982611403F, 8.41939163F, 6.451931F, 9.91021729F, 8.17010784F,
    6.33900452F, 0.264018327F, 3.3027544F, 1.78677988F, 6.77173424F, 1.49555159F,
    3.61530423F, 9.65785217F, 1.39041853F, 9.92997169F, 4.91877317F, 2.81767917F,
    2.13626504F, 9.79324818F, 3.58355665F, 8.63139439F, 3.05209494F, 1.76472187F,
    9.0307188F, 0.0554992259F, 8.23690414F, 6.15907621F, 7.18222809F, 5.1165657F,
    5.6422143F, 3.17093754F, 0.627964854F, 2.112077F, 4.48822546F, 3.4671576F,
    9.06381607F, 0.360507071F, 4.7531662F };

  __attribute__ ((section(".heapsram"))) static const float fv1[4] = { 2.60491562F, 8.3880024F, 9.84814F, 8.3380537F };

  __attribute__ ((section(".heapsram"))) static const float fv2[4] = { 0.363082469F, 7.86419F, 1.84876311F, 8.56158352F
  };

  __attribute__ ((section(".heapsram"))) static const float fv3[400] = { 7.46655798F, 7.54029322F, 6.42056465F,
    4.91659355F, 9.17552757F, 8.87407303F, 8.38288403F, 1.84421432F, 8.51307774F,
    8.57509136F, 4.36606836F, 5.67591F, 8.11050606F, 2.34224486F, 7.44277143F,
    2.58355427F, 2.26851153F, 6.94811487F, 7.91252851F, 2.29028606F, 6.73151302F,
    6.61724901F, 6.03945541F, 0.767894328F, 8.7483139F, 0.751861334F,
    5.07736158F, 3.36002469F, 4.75796556F, 2.20790744F, 1.89020419F, 6.90010595F,
    8.61678219F, 0.118761554F, 8.96011448F, 6.78437185F, 1.74516642F,
    2.03159237F, 7.68141794F, 6.16588593F, 6.47240686F, 0.404817343F,
    2.82369876F, 7.35927343F, 9.11157799F, 0.119515009F, 1.04178131F,
    8.67414665F, 0.837310731F, 7.04847479F, 1.87100923F, 7.65668583F,
    6.60406637F, 5.19821405F, 4.08716965F, 3.75792527F, 8.84190178F, 5.93670702F,
    1.58022583F, 1.41980565F, 4.91031647F, 6.11690426F, 6.91649914F, 7.85144854F,
    9.17375946F, 5.90989733F, 3.71297479F, 9.97649193F, 3.84501219F, 2.58092594F,
    1.63777769F, 0.728175104F, 9.55624866F, 3.36686F, 5.27028513F, 4.95324945F,
    8.17165089F, 8.60668945F, 9.33169746F, 7.12361097F, 2.65319014F, 8.5295639F,
    5.84075165F, 8.5062542F, 6.17448139F, 1.33791411F, 6.88236761F, 5.07264185F,
    6.7683F, 5.97437525F, 4.74926949F, 3.8966918F, 3.12030888F, 0.700063229F,
    5.00304413F, 5.50200558F, 4.97437716F, 9.34476471F, 9.63752174F, 7.78977203F,
    6.28709364F, 3.04526281F, 1.83392036F, 6.60168457F, 1.04157615F, 2.93878627F,
    6.16273F, 1.16349447F, 0.682756186F, 7.13966322F, 0.652945697F, 7.86851788F,
    0.0818286836F, 8.78741455F, 1.12580609F, 1.23864448F, 8.23606682F, 4.40773F,
    3.62137341F, 4.97621775F, 0.864230275F, 1.39210606F, 4.20411873F,
    2.27375221F, 7.56706F, 8.84816F, 3.23490477F, 4.16971827F, 5.41642475F,
    6.1193285F, 3.73695517F, 0.10439378F, 0.743514121F, 1.29522359F,
    0.667237103F, 9.2381258F, 2.63767052F, 1.25973284F, 5.31209707F, 5.93633318F,
    9.60157204F, 3.56537127F, 7.43403816F, 1.03439891F, 4.16563892F, 8.04623604F,
    3.90049148F, 5.37786579F, 9.31440639F, 8.33466339F, 2.44761205F, 8.2813673F,
    1.25614953F, 4.48191738F, 4.13200378F, 6.31609058F, 2.79034901F, 8.26050854F,
    9.43479633F, 6.56235456F, 5.16433096F, 4.62270069F, 7.94929F, 0.307452619F,
    4.58806896F, 4.28010511F, 7.70467091F, 9.91278F, 7.77514076F, 2.2149806F,
    5.43735838F, 6.1807723F, 0.349162072F, 0.343755454F, 7.08067703F,
    2.45081043F, 1.91629767F, 2.57589412F, 2.00575256F, 7.06953621F, 3.27864838F,
    7.86704779F, 2.29533935F, 8.7439537F, 7.28020287F, 5.26380634F, 4.25987577F,
    5.54904604F, 0.203660473F, 4.20468187F, 4.17251682F, 1.30198622F,
    1.39889181F, 7.95604897F, 4.95865917F, 7.03606796F, 3.32772136F, 3.26472354F,
    4.50922155F, 4.51347685F, 3.29541922F, 0.212209523F, 8.6378F, 1.72444856F,
    2.76866722F, 5.7819643F, 0.747831583F, 5.56638813F, 3.19383907F,
    0.888248205F, 8.7928F, 9.46177864F, 4.90451908F, 8.86649895F, 1.65227413F,
    3.17865586F, 6.01074505F, 9.98709774F, 4.85967731F, 7.86674643F, 1.78286052F,
    0.331869513F, 6.59173775F, 7.02037716F, 8.58051205F, 7.87553358F,
    3.84209681F, 4.65951633F, 1.65579319F, 1.71565747F, 7.72324896F, 9.72772503F,
    9.21702766F, 4.40281773F, 1.07385361F, 4.18804121F, 7.84448624F, 5.48594379F,
    8.23597622F, 1.76664221F, 7.50468397F, 8.0774622F, 8.81805706F, 0.176118061F,
    0.81416136F, 0.128951862F, 7.94881678F, 5.0731492F, 4.17415667F, 9.7268734F,
    3.88904643F, 9.89224148F, 3.13775659F, 0.0544690974F, 5.56784868F,
    9.95917797F, 0.637209117F, 6.00591516F, 4.00651646F, 9.5052433F, 9.21265125F,
    5.64886761F, 0.650485337F, 1.54847777F, 1.39189351F, 0.688605189F,
    5.99875355F, 4.51519251F, 7.58335829F, 5.05304718F, 8.77908897F, 4.8985734F,
    8.91293907F, 9.06748581F, 9.80922413F, 8.91360474F, 9.47343349F, 4.66856241F,
    4.60830641F, 4.14254808F, 0.942791164F, 3.125247F, 4.44592953F, 8.48484421F,
    4.68686056F, 9.13215446F, 1.89046657F, 7.90284634F, 9.12099934F, 7.78241348F,
    1.42888832F, 4.62440348F, 6.87530613F, 4.29564428F, 2.83499026F, 7.26769066F,
    5.03827715F, 0.925459802F, 3.4103179F, 6.24984455F, 6.4264245F, 7.51688385F,
    9.20316219F, 1.50000107F, 8.15825558F, 5.9519887F, 8.87026787F, 3.983845F,
    5.59603596F, 4.24901581F, 7.22717094F, 9.61218548F, 1.85726082F,
    0.467430264F, 5.40663385F, 0.8397578F, 3.94372249F, 8.8322525F, 8.69791317F,
    7.67877531F, 4.1318078F, 7.42457438F, 8.72418499F, 1.25492561F, 9.74496555F,
    5.04154539F, 7.57671F, 6.13961935F, 9.45952606F, 1.95237732F, 6.12945318F,
    5.86295271F, 9.58944416F, 5.44467258F, 5.40922546F, 2.12209916F, 8.84950352F,
    5.68828F, 7.99835253F, 0.116607852F, 8.40283108F, 5.78013706F, 4.03064537F,
    5.32506371F, 9.30730057F, 3.66161227F, 9.65868282F, 8.78759766F, 3.73091769F,
    0.644002914F, 4.15237808F, 1.84492874F, 0.398032069F, 1.69039822F,
    2.8304646F, 8.75616741F, 0.549449861F, 9.30727482F, 0.622784257F, 5.32492F,
    1.58320987F, 3.66150236F, 3.58385754F, 5.71344042F, 1.95872295F, 5.36586189F,
    4.21857214F, 1.4495306F, 8.77652F, 8.88121319F, 9.0548048F, 3.53910279F,
    2.97107744F, 9.06117153F, 0.336971939F, 9.29428F, 7.46995068F, 1.75675118F,
    7.2659235F, 5.85605049F, 1.27653539F, 3.05991459F, 4.43252087F, 7.09877777F,
    9.11166668F, 9.01756F, 9.25170422F, 5.75892353F, 5.92726326F, 8.84515095F,
    6.38347292F, 1.60110593F, 8.00941467F, 2.77542353F, 4.41701889F, 4.20061302F,
    2.24543667F, 5.64411068F, 4.56263828F, 1.13914227F };

  __attribute__ ((section(".heapsram"))) static const float fv4[400] = { 0.543887079F, 1.89803934F, 2.68289351F,
    4.33679628F, 7.44293499F, 9.24406338F, 6.38374949F, 6.97672272F,
    0.838285327F, 7.43567562F, 0.832797945F, 6.28573084F, 0.97634095F,
    6.75229788F, 8.19195366F, 4.95482111F, 8.09114552F, 5.07997131F, 4.79978228F,
    3.54787016F, 4.2390151F, 9.328022F, 6.41616535F, 2.70698714F, 8.27036476F,
    3.36048746F, 2.10052299F, 9.6549921F, 3.34692478F, 7.42154884F, 4.02015543F,
    0.248764381F, 6.58188486F, 4.29376125F, 9.24551F, 7.5380888F, 3.26799178F,
    0.94165194F, 7.65116501F, 3.71465158F, 3.43063855F, 5.60120153F, 1.95120931F,
    0.52251637F, 2.86325121F, 9.46129131F, 2.08317137F, 3.42654324F, 9.1433754F,
    9.43257618F, 7.09749508F, 0.223759875F, 5.96763372F, 6.96859646F,
    3.75961256F, 7.81624889F, 0.590517759F, 9.3464241F, 0.808470249F, 1.8762356F,
    8.64141083F, 7.37611532F, 1.67391193F, 7.53778028F, 9.18426228F, 2.08319616F,
    0.872735322F, 6.46524191F, 4.3587265F, 2.80345035F, 8.50572586F, 6.59392F,
    5.66245079F, 6.86786652F, 6.8201251F, 4.25314188F, 2.52018905F, 2.13344574F,
    8.99513054F, 9.2378149F, 6.42488766F, 1.25547338F, 8.55917072F, 5.2403183F,
    5.12796F, 8.75299454F, 7.88222075F, 4.25045824F, 9.47952175F, 0.202449F,
    9.63506413F, 4.74444914F, 1.05871379F, 0.289964408F, 7.50818062F,
    0.906715572F, 9.58357716F, 8.54980755F, 6.65302372F, 0.826881886F,
    9.68164062F, 1.24939227F, 3.72311592F, 9.12567F, 4.35686731F, 1.88090146F,
    1.75810897F, 3.20797706F, 0.37806344F, 1.27223063F, 8.38660908F, 9.48735714F,
    2.76313496F, 8.20837F, 4.13702202F, 4.21630526F, 6.63038349F, 2.35632682F,
    6.35065031F, 6.03752279F, 5.42989F, 4.38498259F, 7.50484848F, 6.25872755F,
    2.97290421F, 4.74229765F, 6.56156111F, 5.90471792F, 2.42553353F,
    0.485026717F, 8.69426823F, 9.41099453F, 8.32077122F, 1.05186236F, 3.3615303F,
    4.02813864F, 0.474626511F, 9.64948368F, 5.38815784F, 6.30443621F,
    6.79869795F, 3.78140473F, 0.150069416F, 3.47381473F, 6.12839937F,
    6.11960363F, 1.44597793F, 5.51101542F, 7.73565245F, 3.85853553F, 7.34164715F,
    3.60595226F, 1.7226063F, 6.75896788F, 8.29788F, 1.70684123F, 3.60642314F,
    2.74480367F, 1.85946155F, 7.69014F, 5.83523369F, 2.24432969F, 9.89836693F,
    1.97124493F, 9.81659222F, 0.438525528F, 3.4861064F, 7.42375183F,
    0.854936659F, 6.05880308F, 9.82998848F, 0.132165521F, 0.95845288F,
    1.40170574F, 3.17045522F, 9.50203419F, 0.213262454F, 4.96370554F, 3.5972538F,
    8.19282246F, 8.91787815F, 2.29390717F, 2.59138417F, 7.9652648F, 1.37497842F,
    5.16678572F, 7.30208921F, 1.81416345F, 3.71726775F, 2.00164557F, 1.15452266F,
    7.51593065F, 6.39483881F, 2.26172733F, 3.56706786F, 3.69667745F, 2.51887321F,
    7.05654573F, 4.73986626F, 2.07946181F, 9.68796062F, 9.88062382F, 3.14007711F,
    7.20534229F, 5.10924721F, 4.46989393F, 6.31389666F, 7.33976126F, 6.64667845F,
    7.56558275F, 0.803492785F, 7.83248F, 5.18120098F, 6.78968811F, 1.39165652F,
    9.57566357F, 2.8699708F, 0.438332677F, 6.87703228F, 7.49757242F, 2.9915874F,
    1.44451702F, 9.64792442F, 3.42268729F, 7.80340433F, 1.38340378F,
    0.621799052F, 9.21242809F, 7.16965342F, 7.45643711F, 7.85329199F,
    4.20017433F, 3.04526806F, 1.42347741F, 8.76340389F, 2.23749542F, 8.66349506F,
    5.20063162F, 7.29993868F, 1.16912127F, 7.90724134F, 3.58763456F, 1.45461118F,
    2.97763801F, 0.917574704F, 8.09514713F, 3.54601097F, 0.938116074F,
    6.48690844F, 8.79942417F, 3.58287644F, 1.74150443F, 9.46735096F, 8.5376873F,
    3.46724892F, 0.710612476F, 3.82391334F, 2.93271399F, 1.00414073F,
    5.10699129F, 1.60107565F, 1.66614F, 5.61240482F, 3.37189F, 0.060964413F,
    2.42278886F, 9.5837F, 0.202598989F, 6.07660532F, 8.02635479F, 0.971176445F,
    7.68988132F, 9.091712F, 0.648213744F, 6.75407028F, 8.86517048F, 6.03224564F,
    2.71539259F, 3.36665893F, 8.4593153F, 0.0401496328F, 2.49076962F, 8.62354F,
    5.31026506F, 4.99823856F, 8.28908253F, 9.1875124F, 1.14616656F, 7.16178179F,
    3.82164979F, 0.266677111F, 9.68988323F, 4.50749254F, 5.72248507F,
    9.10776615F, 8.90694F, 9.60933304F, 2.73412609F, 7.525033F, 2.04345846F,
    7.28859329F, 9.71088791F, 3.18025827F, 6.34713459F, 0.439795554F,
    2.14580846F, 2.8827374F, 9.67525578F, 7.89472389F, 8.72498F, 8.05918312F,
    3.51637197F, 6.81154156F, 2.65036845F, 3.96087837F, 1.77753448F, 3.95693183F,
    9.52182674F, 1.30800378F, 4.52864313F, 3.9115119F, 1.34222305F, 7.14406729F,
    1.63172603F, 4.77991915F, 0.462709874F, 5.84669352F, 3.07146406F,
    4.53165817F, 3.53319621F, 2.52254581F, 5.97019529F, 5.96446228F, 8.80330658F,
    9.64445877F, 2.21521473F, 1.15680933F, 9.29584789F, 1.58416677F,
    0.992061079F, 3.72038388F, 1.27277446F, 7.21075487F, 9.92817211F,
    5.83595324F, 9.86308765F, 1.38254905F, 6.85252F, 4.76568842F, 3.06240058F,
    7.90088224F, 6.23122835F, 4.76891613F, 0.229175583F, 5.93440437F,
    6.95574808F, 1.33512378F, 6.73799133F, 1.58010697F, 5.46453428F, 4.97258186F,
    4.28685665F, 5.66627836F, 8.88441F, 2.43622947F, 6.12593365F, 8.23528767F,
    5.99672031F, 2.00458264F, 5.37972546F, 9.80748272F, 7.94556904F, 6.91117F,
    8.70908546F, 2.239079F, 0.341001362F, 1.35397148F, 3.85830617F, 1.00463223F,
    6.42483854F, 6.62763834F, 9.91563702F, 5.98087F, 6.44588423F, 0.542683482F,
    5.54141712F, 7.04306889F, 4.14420605F, 4.1296649F, 2.33448434F, 1.12682593F,
    9.93906116F, 1.98285627F, 4.52836561F, 0.336863935F, 7.30129671F,
    6.38712215F, 0.142991185F, 7.22341919F, 5.26229811F };

    static const float fv5[16] = { 11456.2139F, 11455.9854F, 626.878F, 626.865417F,
    166939.125F, 166935.781F, 264863.0F, 264857.688F, 54308.8672F, 54307.7812F,
    24403.5742F, 24403.0859F, 230735.609F, 230730.984F, 409132.25F, 409124.062F
  };

/////////////////////////////////////////////////////////
// subfunctions
/////////////////////////////////////////////////////////


float sum(const float x[100])
{
  float y;
  int k;
  y = x[0];
  for (k = 0; k < 99; k++) {
    y += x[k + 1];
  }

  return y;
}

float var(const float x[100])
{
  float y;
  int ix;
  float xbar;
  int k;
  float r;
  ix = 0;
  xbar = x[0];
  for (k = 0; k < 99; k++) {
    ix++;
    xbar += x[ix];
  }

  xbar *= 1.0F/100.0F;
  ix = 0;
  r = x[0] - xbar;
  y = r * r;
  for (k = 0; k < 99; k++) {
    ix++;
    r = x[ix] - xbar;
    y += r * r;
  }

  y *= 1.0F/99.0F;
  return y;
}

boolean_T checkRes(const float check[2], const float golden[4])
{
  int k;
  boolean_T y = true;
  for (k = 0; k < 2; k++) {
    y = y && (check[k] <= golden[k << 1]);
    y = y && (check[k] >= golden[1 + (k << 1)]);
    printErrors(!y, k, check[k], golden[k<<1], golden[1+(k<<1)]);
  }

  return y;
}

void mlGemm(const float A[100], const float B[100], float C[100], float a, float
            b)
{
  int i2;
  int i3;
  float f0;
  int i4;

  /*  mlGemm */
  for (i2 = 0; i2 < 10; i2++) {
    for (i3 = 0; i3 < 10; i3++) {
      f0 = 0.0F;
      for (i4 = 0; i4 < 10; i4++) {
	f0 += a * A[i2 + 10 * i4] * B[i4 + 10 * i3];
      }
      C[i2 + 10 * i3] = f0 + b * C[i2 + 10 * i3];
    }
  }
}

/////////////////////////////////////////////////////////
// main testing function 
/////////////////////////////////////////////////////////
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  int coreid;
  int it;

  boolean_T pass;
  float C[100];
  int i0;
  int i1;
  float f0;
  int i2;
  float tmp[2];


  /////////////////////////////////////////////////////////
  // main test loop 
  // each core loops over a kernel instance
  /////////////////////////////////////////////////////////
  
  
  coreid = get_core_id();

  printf("starting %d kernel iterations... (coreid = %d)\n",KERNEL_ITS,coreid);

  if (coreid>3)
    coreid=coreid-4;

  synch_barrier();

  perf_begin();

  for(it = 0; it < getKernelIts(); it++)
  {
    // matlab kernel
    for (i0 = 0; i0 < 10; i0++) {
      for (i1 = 0; i1 < 10; i1++) {
	C[i1 + 10 * i0] = fv0[(i1 + 10 * i0) + 100 * coreid];
      }
    }
  
    mlGemm(*(float (*)[100])&fv4[100 * coreid], *(float (*)[100])&fv3[100 * coreid], C, fv2[coreid], fv1[coreid]);
  }

  synch_barrier();

  perf_end();

  synch_barrier();

  /////////////////////////////////////////////////////////
  // check results
  /////////////////////////////////////////////////////////
  
  tmp[0] = sum(C);
  tmp[1] = var(C);
  pass = checkRes(tmp, *(float (*)[4])&fv5[coreid << 2]);
  flagPassFail(pass, get_core_id());
  

/////////////////////////////////////////////////////////
// synchronize and exit
/////////////////////////////////////////////////////////

  return !pass;
}

