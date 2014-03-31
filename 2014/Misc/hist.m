%                      ______________________________________
%             ________|                                      |_______
%             \       |            I Like Fish               |      /
%              \      | TANG Zhixiong          2011302590011 |     /
%              /      |______________________________________|     \
%             /__________)                                (_________\
%         
% ========================================================================================
%
%    #         #          #    #    #  ######           ######     #     ####   #    #                    % @author: TANG Zhixiong
%    #	       #          #    #   #   #     	        #          #    #       #    #			  % @email: gnat_tang@yeah.net				    
%    #	       #          #    ####    ##### 	        #####      #     ####   ######			  % @whu_id: 2011302590011
%    #	       #          #    #  #    #     	        #          #         #  #    #			  % @datetime: 10:53:42, Monday, March 31 2014		    
%    #	       #          #    #   #   #     	        #          #    #    #  #    #			  % @ongithub:                                                
%    #	       ######     #    #    #  ######	        #          #     ####   #    #                    % @
%
% ========================================================================================
					   













%            #####
%           #### _\_  ________
%           ##=-[.].]| \      \      I'm a coder
%           #(    _\ |  |------|     Coder at work
%            #   __| |  ||||||||
%             \  _/  |  ||||||||
%          .--'--'-. |  | ____ |
%         / __      `|__|[o__o]|
%       _(____nm_______ /____\____
% ===============================================================
function varargout = histogram(varargin)
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @histogram_OpeningFcn, ...
                   'gui_OutputFcn',  @histogram_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end




%            
%                  __            /^\
%                .'  \          / :.\   
%               /     \         | :: \ 
%              /   /.  \       / ::: | 
%             |    |::. \     / :::'/  
%             |   / \::. |   / :::'/
%             `--`   \'  `~~~ ':'/`
%                     /         (    
%                    /   0 _ 0   \   
%                  \/     \_/     \/  
%                -== '.'   |   '.' ==-      I like rabbits
%                  /\    '-^-'    /\        but not rabbit soup
%                    \   _   _   /             
%                   .-`-((\o/))-`-.   
%              _   /     //^\\     \   _    
%            ."o".(    , .:::. ,    )."o".  
%            |o  o\\    \:::::/    //o  o| 
%             \    \\   |:::::|   //    /   
%              \    \\__/:::::\__//    /   
%               \ .:.\  `':::'`  /.:. /      
%                \':: |_       _| ::'/  
%             jgs `---` `"""""` `---`
% =======================================================================================
function histogram_OpeningFcn(hObject, ~, handles, varargin)
handles.output = hObject;
guidata(hObject, handles);

function varargout = histogram_OutputFcn(~, ~, handles) 
varargout{1} = handles.output;

function edit_max_Callback(hObject, eventdata, handles)

function edit_max_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




%                              _ _
%                 ____________/ / \_.)_
%                 `.     ,'   @_@_/ ,'|
%                   `-.-'        , / /|          Dog is cute too
%                      `-.____,-'  | ||
%                               \  \ ||
%                               |  | \|
%                              /   \     ,,'
%                              |    \   //
%                             /      |  ||
%                             |    ,-\ //
%                             |   _\  \||
%                            (_`-(_____)/  -Shimrod
% =======================================================================================
function edit_min_Callback(hObject, eventdata, handles)
function edit_min_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

function menu_document_open_Callback(~, ~, handles)
global im
[filename,pathname]=...
    uigetfile({'*.*';'*.bmp';'*.tif';'*.png'},'select picture');
str=[pathname filename];
im=imread(str);
axes(handles.axes_imviewer);  
imshow(im);


function menu_histogram_red_Callback(~, ~, handles)
global im
if size(im,3) == 3
[counts,x] = imhist(im(:,:,1));
meanValue = mean(counts);
set(handles.edit_mean,'String',num2str(meanValue));
varValue = var(counts);
set(handles.edit_variance,'String',num2str(varValue));
maxValue = max(max(im(:,:,1)));
set(handles.edit_max,'String',num2str(maxValue));
minValue = min(min(im(:,:,1)));
set(handles.edit_min,'String',num2str(minValue));
axes(handles.axes_histogram);
bar(x,counts,'r');
end





%
%                        _ ___                /^^\ /^\  /^^\_
%            _          _@)@) \            ,,/ '` ~ `'~~ ', `\.
%          _/o\_ _ _ _/~`.`...'~\        ./~~..,'`','',.,' '  ~:     crocodile
%         / `,'.~,~.~  .   , . , ~|,   ,/ .,' , ,. .. ,,.   `,  ~\_  not cute
%        ( ' _' _ '_` _  '  .    , `\_/ .' ..' '  `  `   `..  `,   \_
%         ~V~ V~ V~ V~ ~\ `   ' .  '    , ' .,.,''`.,.''`.,.``. ',   \_
%          _/\ /\ /\ /\_/, . ' ,   `_/~\_ .' .,. ,, , _/~\_ `. `. '.,  \_
%         < ~ ~ '~`'~'`, .,  .   `_: ::: \_ '      `_/ ::: \_ `.,' . ',  \_
%          \ ' `_  '`_    _    ',/ _::_::_ \ _    _/ _::_::_ \   `.,'.,`., \-,-,-,_,_,
%           `'~~ `'~~ `'~~ `'~~  \(_)(_)(_)/  `~~' \(_)(_)(_)/ ~'`\_.._,._,'_;_;_;_;_;
%
%
% =========================================================================================      
function menu_histogram_green_Callback(~, ~, handles)
global im
if size(im,3) == 3
[counts,x] = imhist(im(:,:,2));
meanValue = mean(counts);
set(handles.edit_mean,'String',num2str(meanValue));
varValue = var(counts);
set(handles.edit_variance,'String',num2str(varValue));
maxValue = max(max(im(:,:,2)));
set(handles.edit_max,'String',num2str(maxValue));
minValue = min(min(im(:,:,2)));
set(handles.edit_min,'String',num2str(minValue));
axes(handles.axes_histogram);
bar(x,counts,'g');
end

function menu_histogram_blue_Callback(~, ~, handles)
global im
if size(im,3) == 3
[counts,x] = imhist(im(:,:,3));
meanValue = mean(counts);
set(handles.edit_mean,'String',num2str(meanValue));
varValue = var(counts);
set(handles.edit_variance,'String',num2str(varValue));
maxValue = max(max(im(:,:,3)));
set(handles.edit_max,'String',num2str(maxValue));
minValue = min(min(im(:,:,3)));
set(handles.edit_min,'String',num2str(minValue));
axes(handles.axes_histogram);
bar(x,counts,'b');
end


function menu_document_rgb2gray_Callback(hObject, eventdata, handles)
global im 
if size(im,3) == 3
    im = rgb2gray(im);
    axes(handles.axes_imviewer);
    imshow(im);
end


%         
%                    \.   \.      __,-"-.__      ./   ./
%                \.   \`.  \`.-'"" _,="=._ ""`-.'/  .'/   ./
%                 \`.  \_`-''      _,="=._      ``-'_/  .'/
%                  \ `-',-._   _.  _,="=._  ,_   _.-,`-' /
%               \. /`,-',-._"""  \ _,="=._ /  """_.-,`-,'\ ./
%                \`-'  /    `-._  "       "  _.-'    \  `-'/
%                /)   (         \    ,-.    /         )   (\
%             ,-'"     `-.       \  /   \  /       .-'     "`-,
%           ,'_._         `-.____/ /  _  \ \____.-'         _._`,
%          /,'   `.                \_/ \_/                .'   `,\
%         /'       )                  _            Krogg (       `\
%                 /   _,-'"`-.  ,++|T|||T|++.  .-'"`-,_   \
%                / ,-'        \/|`|`|`|'|'|'|\/        `-, \
%               /,'             | | | | | | |             `,\
%              /'               ` | | | | | '               `\
%                                 ` | | | '
%                                   ` | '     Windows die
%                                             Human   die
% ==============================================================================
function menu_histogram_gray_Callback(hObject, eventdata, handles)
global im
if size(im,3) == 1
[counts,x] = imhist(im);
meanValue = mean(counts);
set(handles.edit_mean,'String',num2str(meanValue));
varValue = var(counts);
set(handles.edit_variance,'String',num2str(varValue));
maxValue = max(max(im));
set(handles.edit_max,'String',num2str(maxValue));
minValue = min(min(im));
set(handles.edit_min,'String',num2str(minValue));
axes(handles.axes_histogram);
bar(x,counts,'k');
end


function figure1_ResizeFcn(~, ~, handles)
% ========================================================================================         
%                                  .__              .
%                                  [__)  _   _.  _. |_
%                                  [__) (/, (_]_(_. [ )
%                             .  .
%                             \  / _  ._. _  ._   *   _.  _.
%                              \/ (/, [  (_) [ )  |  (_. (_]_
%         
%         
%         
%         
%                                       _.-----,._
%                                     .'          `.
%                                    /              \
%                                   /                \
%                            ______/__________________\______
%                         .-----------------------------------.
%                        (        |  /         `.  \  |        ) Llizards hat
%                         ` .     |  |           `.   |    . '
%                             ` . |  |.---.   .---.\  |. '
%                                 | |( //%          )=(///%          )` | <---reflective shades
%                                 |  |`---'/ \`---'|| |
%                                 |  |    ((_))    |  |
%                                 | `|`  /__ __\  '|  |
%                                 |  |   <--=-->   |  | <---kissy lips
%                                 /  /    `---'    |  |
%                                /   |`.    "    .'/  \
%                               / / | | `-.___.-' ||   \
%                              /     '|           |  \  \
%                             /'  /   |           |\   ` \
%                            /   .  /-'           `-n.__ \\
%                           / .-'| |H      l_       H   `-.\
%                          /.'  / / H               H      `.
%                         .'   | |  H               H        `.
%                       .'          H               H        o `.  <---Mermaid tatoo
%                     .'            F\             /R         %         _,`.
%                   .'             /  \           /  \             `.
%                 .'             ./    `.       ,'    \,             `.
%                /            /,'/       \.   ./       \`,\            \
%              .'            J: /         \`.'/         \ :F            `.
%             /            .'|l/           \"/           \;|`.            \
%           .'           .'  `(            {=}            )'  `.           `.
%          /           .'     (     ()     {=}     ()     )     `.           \
%         (          .'       (            /:\            ) <-----`.          )------bikini top
%          \       .'         J\          /,".\          /F         `.       /
%           \      \           F`.______,''   ``.______,'J           /      /
%            \      \    ___   F                         J          /      /
%             \      \,-'   \  |                         |         /      /
%              \     / ====  \ |                         |        /      /
%               \   /   === \ \|                         |       /      /
%                \ // //.'___ \|                         |      (      /
%                 / /// %         `._\  F                         J   _.' `.   /
%                / //  %             \\,F                         J  /      `./:  <--Bracelet with key
%               / /   %               \/`.          (@)          ,'\/        /`Y
%              /  /  %               ./`. ',                   ,' ,'\.      J  F
%             // /  %         |     ./   `. \                 / ,'   \.     |
%            J  (   F \   ./      \ \               / /      \.   /
%            J   |  F  \_./        \ \             / /        \._/
%            J |||  F     J         \ `.         ,' /         F
%            J  |   F     |          \  `._____,'  /          |
%            J  |   F     |           \           /           |
%            J  |  \\\    |            \         /            |<--lil shave and a bikini
%            J,:;.,.;.:   |             \       /             |
%                         |              \     /              |
%                A        J               `._,'               F
%                |        J                 Y                F
%                `--towel  F                |                J
%                          F                |                J
%                          |                |                |
%                          J                |                F
%                          J                |                F
%                           F               |               J
%                           F               |               J
%                           |               ^               |
%                           J              J F              F
%                           J              | |              F
%                            F             | |             J
%                            F             | |             J
%                            |             | |             |
%                            |             | |             |
%                            J             F J             F
%                            J             F J             F
%                             F           J   F           J
%                             F  /      \ J   F /      \  J
%                             |           |   |           |
%                             |           |   |           |
%                             |           |   |           |
%                             J  \      / F   J \      /  F
%                             J           F   J           F
%                              F         J     F         J
%                              F         J     F         J
%                              |         |     |         |
%                              |         |     |         |
%                              |         |     |         |
%                              |         |     |         |
%                              |         |     |         |
%                              |         |     |         |
%                              |         |     |         |
%                              J         F     J         F
%                              J         F     J         F
%                               F       J       F       J
%                               F       J       F       J
%                               |       |       |       |
%                               |       |       |       |
%                               |       |       |       |
%                               |       |       :.     .: <--anklet
%                               (       |       |`:::::')
%                               F`.    _J       F_    .'J
%                              J `.`. /_ F     J _\ .'.' F <--Llizard's sandles
%                             / _ _`.V/==\\   //==\V.'_ _ \
%                            (_(_(_(_)\__//   \\__/(_)_)_)_)
%                             ============     ============
%         
% 

% 

% ============================================================================================
%         
%          #####    #   #  ######
%          #    #    # #   #
%          #####      #    #####   
%          #    #     #    #        
%          #    #     #    #         ###  
%          #####      #    ######    ###  
%         			    #    
%         			   #     						
%          				  #    #    ##     #####  #         ##    #####	
%         				  ##  ##   #  #      #    #        #  #   #    #	
%         				  # ## #  #    #     #    #       #    #  #####	
%         				  #    #  ######     #    #       ######  #    #	
%         				  #    #  #    #     #    #       #    #  #    #	
%         				  #    #  #    #     #    ######  #    #  #####  
%         
% ===========================================================================================
